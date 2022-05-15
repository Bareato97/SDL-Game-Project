#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class EntityManager;

// Component variables
using ComponentID = std::size_t;

// gets the last component id, storing the amount of components
inline ComponentID getComponentTypeID(){

    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
    
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

// max amount of components an entity can have
constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;


// Group variables
// max amount of render layors
using Group = std::size_t; // utilised for render layers
constexpr std::size_t maxGroups = 32;
// Create group bitset
using GroupBitset = std::bitset<maxGroups>;

// Classes

class Component{
    
    public:
        // Component contains a reference to its entity
        Entity* entity;

        virtual void init(){}
        virtual void update(){}
        virtual void draw(){}
        virtual ~Component(){}
};

class Entity{

    private:

        // EntityManager contains a list of entities, and entities can reference the entityEntityManager
        EntityManager& manager;

        // Checks if entities
        bool active = true;
        std::vector<std::unique_ptr<Component>> componentList;

        ComponentArray componentArray;
        ComponentBitSet componentBitSet;

        GroupBitset groupBitset;

    public:

        // Initialise group labels, max 32 labels
        enum groupLabels : std::size_t {
            groupMap,
            groupPlayer,
            groupEnemies,
            groupColliders
        };

        Entity(EntityManager& mEntityManager) : manager(mEntityManager) {}

        void update(){

            for(auto& c : componentList) c->update(); // Cycles through components 
        }
        void draw(){

            for(auto& c : componentList) c->draw();
        }

        ~Entity(){
            std::cout << "entity destroyed" << std::endl;
        }

        bool isActive() const {return active;}
        void destroy() {active = false;}

        // Check if entity is part of a group
        bool hasGroup(Group mGroup) { 

            return groupBitset[mGroup];
        }

        // Adds entity to a group, entity can be part of multiple groups
        void addGroup(Group mGroup);

        // Removes entity from a group
        void delGroup(Group mGroup){

            groupBitset[mGroup] = false;
        }

        // template function to see if an entity has a component
        template <typename T> bool hasComponent() const {

            return componentBitSet[getComponentTypeID<T>()];
        }  

        // Handles adding components with a variable number of arguments
        template <typename T, typename... TArgs>
        T& addComponent(TArgs&&... mArgs){

            T* c(new T(std::forward<TArgs>(mArgs)...));
            c->entity = this;
            std::unique_ptr<Component> uPtr{ c };
            componentList.emplace_back(std::move(uPtr));

            componentArray[getComponentTypeID<T>()] = c;
            componentBitSet[getComponentTypeID<T>()] = true;

            c->init();
            return *c;
        }

        // used to return specific components e.g. object.getComponent<T>().getHealth()
        template<typename T> T& getComponent() const {

            auto ptr(componentArray[getComponentTypeID<T>()]);
            return *static_cast<T*>(ptr);
        }
};

// holds list of all entities
class EntityManager{
    
    private:
        
        // these hold the list of components an entity has, as well as the active groups
        std::vector<std::unique_ptr<Entity>> entityList;
        std::array<std::vector<Entity*>, maxGroups> groups;

    public:
        
        // TODO - re-evaluate update method, as components hold a reference to their entity, might be able to create a list of components and call them, rather than call on entity to them perform component function
        // Reason being to reduce cache misses, and reduced space as memory is called into L1 cache
        void update(){

            for (auto& e : entityList) e->update();
        }
        
        void draw(){

            for (auto& e : entityList) e->draw();
        }

        // removes inactive entities
        void refresh(){
            
            // removes groups
            for(auto i(0u); i < maxGroups; i++){ // iterate through array

                auto& v(groups[i]);
                v.erase( // iterate through vector, removing from group manger if it inactive, or if it doesnt have that group anymore
                    std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity){
                        return !mEntity->isActive() || !mEntity->hasGroup(i);
                    }), std::end(v));
            }

            // removes entity from manager if it is no longer active
            entityList.erase(std::remove_if(std::begin(entityList), std::end(entityList), [](const std::unique_ptr<Entity> &mEntity) {

                return !mEntity->isActive(); // returns true if entity is inactive, as remove_if removes entry if it is true
            }),
            std::end(entityList));
        }

        // Add entity reference to desired group
        void addToGroup(Entity* mEntity, Group mGroup){

            groups[mGroup].emplace_back(mEntity);
        }

        // returns the entities of a specified group
        std::vector<Entity*>& getGroup(Group mGroup){

            return groups[mGroup];
        }

        // adds an entity to the entity list
        Entity& addEntity(){

            Entity* e = new Entity(*this); // Create temporary entity
            std::unique_ptr<Entity> uPtr{ e }; // establish unique pointer for the new entity
            entityList.emplace_back(std::move(uPtr)); // adds the entity to the entitymanager list
            return *e;
        }
};