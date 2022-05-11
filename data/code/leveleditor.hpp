#pragma once

#include "vector"
#include "string"
#include "utility"
#include "map"

#include "ECS/components.hpp"

class LevelEditor {
private:

    int mapWidth, mapHeight;
    int xTiles, yTiles;
    int** tileMap;
    int tileSize;
    int mX, my;

    bool canCheck = true;

    std::map<int,int> tileIndex; 

public:

    EntityManager* EntityList;
    
    LevelEditor(int mWidth, int mHeight, int tS, EntityManager* manager);

    ~LevelEditor();

    int CheckTiles(int mX, int mY);

    void AddTile(int xIndex, int yIndex, int *tileValue);

    void SaveLevel();

    void LoadLevel();

    void update();

    void InitialiseIndexMap();

};