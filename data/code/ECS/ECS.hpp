#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t; // utilised for render layers

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

// max amount of render layors
constexpr std::size_t maxGroups = 32;

using GroupBitset = std::bitset<maxGroups>;


class Component{
    
    public:
        Entity* entity;

        virtual void init(){}
        virtual void update(){}
        virtual void draw(){}
        virtual ~Component(){}
};

class Entity{

    private:

        Manager& manager;

        bool active = true;
        std::vector<std::unique_ptr<Component>> componentList;

        ComponentArray componentArray;
        ComponentBitSet componentBitSet;

        GroupBitset groupBitset;

    public:

        Entity(Manager& mManager) : manager(mManager) {}

        void update(){

            for(auto& c : componentList) c->update(); 
        }
        void draw(){

            for(auto& c : componentList) c->draw();
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
class Manager{
    
    private:
        
        std::vector<std::unique_ptr<Entity>> entityList;
        std::array<std::vector<Entity*>, maxGroups> groups;

    public:
        
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

                return !mEntity->isActive();
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

            Entity* e = new Entity(*this);
            std::unique_ptr<Entity> uPtr{ e };
            entityList.emplace_back(std::move(uPtr));
            return *e;
        }
};