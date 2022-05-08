#include "ECS.hpp"

// Adds a group to an entity, and an entity to a group
// Both hold a reference to eachother

void Entity::addGroup(Group mGroup){
    
    groupBitset[mGroup] = true;
    manager.addToGroup(this, mGroup); // 
}