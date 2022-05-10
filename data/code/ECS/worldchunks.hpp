#pragma once

#include "components.hpp"

struct WorldChunk {

    bool isLoaded = false;
    EntityManager chunkEntityManager;
    int numEntities;
    int numTileLayers;
    /*
        World chunk is passed a list of entities to build as well as tile information
        chunk is passed a spreadsheet of each entity and what function to call to build it

    */

    WorldChunk(int ne){
        numEntities = ne;
    }

    void LoadChunk() {
        /*
            for(int i = 0; i < numEntities; i++){
                createdEntity();
            }
        */
    }

    void DeloadChunk() {

    }

};