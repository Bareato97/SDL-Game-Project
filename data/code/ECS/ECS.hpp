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

// gets the last component id, storing the amount of components
inline ComponentID getComponentTypeID(){

    static ComponentID lastID = 0;
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
        bool active = true;
        std::vector<std::unique_ptr<Component>> componentList;

        ComponentArray componentArray;
        ComponentBitSet componentBitSet;

    public:
        void update(){

            for(auto& c : componentList) c->update(); 
        }
        void draw(){

            for(auto& c : componentList) c->draw();
        }

        bool isActive() const {return active;}
        void destroy() {active = false;}

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
    
    public:
        
        void update(){

            for (auto& e : entityList) e->update();
        }
        
        void draw(){

            for (auto& e : entityList) e->draw();
        }

        // removes inactive entities
        void refresh(){
            entityList.erase(std::remove_if(std::begin(entityList), std::end(entityList), [](const std::unique_ptr<Entity> &mEntity) {

                return !mEntity->isActive();
            }),
            std::end(entityList));
        }

        // adds an entity to the entity list
        Entity& addEntity(){

            Entity* e = new Entity();
            std::unique_ptr<Entity> uPtr{ e };
            entityList.emplace_back(std::move(uPtr));
            return *e;
        }
};