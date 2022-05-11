#include "leveleditor.hpp"
#include "game.hpp"




LevelEditor::LevelEditor(int mWidth, int mHeight, int tS, EntityManager* manager){

    InitialiseIndexMap();

    EntityList = manager;

    mapWidth = mWidth;
    mapHeight = mHeight;
    tileSize = tS;

    yTiles = mapHeight/tileSize;
    xTiles = mapWidth/tileSize;

    tileMap = new int*[yTiles];
    for(int i = 0; i < yTiles; i++){

        tileMap[i] = new int[xTiles];
        for(int j = 0; j < xTiles; j++){

            tileMap[i][j] = 0;
        }
    }
};

LevelEditor::~LevelEditor(){
    /*
    for(int i = 0; i < yTiles; i++){

        delete tileMap[i];     
    }

    delete tileMap;*/
};

void LevelEditor::update(){

    if(canCheck){
        canCheck = false;
        int mouseX, mouseY;
        Uint32 buttons;

        buttons = SDL_GetMouseState(&mouseX, &mouseY);
        int mouseIndexX = mouseX / tileSize;
        int mouseIndexY = mouseY / tileSize;
        tileMap[mouseIndexY][mouseIndexX] = tileIndex[CheckTiles(mouseIndexX, mouseIndexY)];
        AddTile(mouseIndexX, mouseIndexY, &tileMap[mouseIndexY][mouseIndexX]);
        canCheck = true;   
    }                   
}

int LevelEditor::CheckTiles(int mX, int mY){


    int mouseX = mX;
    int mouseY = mY;

    int tileValue = 0u;

    for(int y = -1; y <= 1; y++) {

        for(int x = -1; x <= 1; x++) {

            if( !(x == 0 && y == 0)) { 

                tileValue = tileValue >> 1; // shift right
                if((mouseX + x >= 0) && ((mouseX + x) <= xTiles) &&
                   (mouseY + y >= 0) && ((mouseY + y) <= yTiles)) {
                    if(tileMap[mouseY + y][mouseX + x] != 0){
                        if(x == -1 && y == -1){

                            if(tileMap[mouseY-1][mouseX] !=0 && tileMap[mouseY][mouseX -1] !=0){
                                tileValue+=128;
                            }
                        }
                        else if(x == 1 && y == 1){

                            if(tileMap[mouseY + 1][mouseX] !=0 && tileMap[mouseY][mouseX + 1] !=0){
                                tileValue+=128;
                            }
                        }
                        else if(x == -1 && y == 1){

                            if(tileMap[mouseY][mouseX - 1] !=0 && tileMap[mouseY + 1][mouseX] !=0){
                                tileValue+=128;
                            }
                        }
                        else if(x == 1 && y == -1){

                            if(tileMap[mouseY][mouseX + 1] !=0 && tileMap[mouseY - 1][mouseX] !=0){
                                tileValue+=128;
                            }
                        }else {
                            tileValue+=128;  
                        }
                    }   
                }   
            }
        }
    }
    
    return tileValue;
};

void LevelEditor::AddTile(int xIndex, int yIndex, int* tileValue){

    
    int destX = xIndex * tileSize;
    int destY = yIndex * tileSize;

    auto& tile(EntityList->addEntity());
    tile.addComponent<TileComponent>(tileValue, destX, destY, "data/art/maps/tilemapdemo.png");
    //tile.addComponent<ColliderComponent>("tile",tileSize, tileSize);
    
    for(int x = -1; x <= 1; x++) {

        for(int y = -1; y <= 1; y++) {

            if((x != 0 || y != 0) &&
            (xIndex + x != -1) && (xIndex + x != mapWidth / tileSize) &&
            (yIndex + y != -1) && (yIndex + y != mapHeight / tileSize)) {
                
                if(tileMap[yIndex + y][xIndex + x] != 0){
                    tileMap[yIndex + y][xIndex + x] = tileIndex[CheckTiles(xIndex + x, yIndex + y)];
                }
            }
        }
    }
    
};

//void LevelEditor::UpdateTile(int xIndex, int yIndex){};

void LevelEditor::SaveLevel(){};

void LevelEditor::LoadLevel(){};

void LevelEditor::InitialiseIndexMap(){

    tileIndex.emplace(2,36);
    tileIndex.emplace(8,39);
    tileIndex.emplace(10,27);
    tileIndex.emplace(11,47);
    tileIndex.emplace(16,37);
    tileIndex.emplace(18,25);
    tileIndex.emplace(22,44);
    tileIndex.emplace(24,38);
    tileIndex.emplace(26,26);
    tileIndex.emplace(27,42);
    tileIndex.emplace(30,41);
    tileIndex.emplace(31,45);
    tileIndex.emplace(64,12);
    tileIndex.emplace(66,24);
    tileIndex.emplace(72,3);
    tileIndex.emplace(74,15);
    tileIndex.emplace(75,31);
    tileIndex.emplace(80,1);
    tileIndex.emplace(82,13);
    tileIndex.emplace(86,28);
    tileIndex.emplace(88,2);
    tileIndex.emplace(90,14);
    tileIndex.emplace(91,34);
    tileIndex.emplace(94,7);
    tileIndex.emplace(95,46);
    tileIndex.emplace(104,11);
    tileIndex.emplace(106,19);
    tileIndex.emplace(107,35);
    tileIndex.emplace(120,6);
    tileIndex.emplace(122,21);
    tileIndex.emplace(123,23);
    tileIndex.emplace(126,21);
    tileIndex.emplace(127,30);
    tileIndex.emplace(208,8);
    tileIndex.emplace(210,16);
    tileIndex.emplace(214,20); //214
    tileIndex.emplace(216,5);
    tileIndex.emplace(218,43);
    tileIndex.emplace(219,34);
    tileIndex.emplace(222,32);
    tileIndex.emplace(223,29);
    tileIndex.emplace(248,10);
    tileIndex.emplace(250,9);
    tileIndex.emplace(251,18);
    tileIndex.emplace(254,17);
    tileIndex.emplace(255,33);
    tileIndex.emplace(0,22);

};