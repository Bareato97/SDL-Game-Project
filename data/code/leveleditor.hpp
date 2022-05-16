#pragma once

#include "vector"
#include "string"
#include "utility"
#include "map"

#include "ECS/components.hpp"

class LevelEditor {
private:

    const char* tileSetPaths; // List of filepaths to tilemap images

    SDL_Texture* tileMapTexture; // source texture for tilemap
    SDL_Texture* combinedTexture;

    SDL_Rect srcRect;
    SDL_Rect desRect;

    std::pair<int,int>** tileMap; // 2D array to store tile values, Tiletype, tileValue
    int mapWidth, mapHeight; // map width and height in pixels
    int mapIndex; // index of the map, eg town might be index 1, forest 2 etc
    int xTiles, yTiles; // number of x and y in tiles
    int tileSize; // size of the tiles
    float tileScale; //  scale of tiles on screen
    int prevMouseX, prevMouseY; // location of the mouseX and mouseY on previous frame
    Uint32 prevButton = 4; // defaults to right click
    int layerLevel;
    int tileType = 1; // used for verifying different tile types, for now defaults to 1 for grass tiles, will convert to an enum at a later date

    // enum entityList TODO: implement system for storing entities to be used

    bool canCheck = true; // bool that is false if the editor is currentll adding a tile, to prevent multiple tiles added at once
    bool sameTile = false; // used to adding multiple tiles, so it wont continuously add to the same tile index

    // Map to convert binary values to an index in the tilemap texture, refer to map implementation and source image for layout, top right is 0,0
    // converts single int to 2d array coordinators
    std::map<int,int> tileIndex; 

public:
    
    LevelEditor(int mWidth, int mHeight, int tSize, float scale);

    ~LevelEditor();

    int CheckTiles(int mX, int mY, int tType);

    void AddTile(int xIndex, int yIndex, int *tileValue);

    void RemoveTile(int xIndex, int yIndex);

    void UpdateNearbyTiles(int xIndex, int yIndex, int tType);

    void updateTexture();

    void SaveLevel();

    void LoadLevel();

    void update(int mouseX, int mouseY, Uint32 button);

    void InitialiseIndexMap();

    void DrawLevel();

};