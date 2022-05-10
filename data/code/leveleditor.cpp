#include "leveleditor.hpp"
#include "game.hpp"

LevelEditor::LevelEditor(int mWidth, int mHeight, int tS, EntityManager* manager){

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

            tileMap[i][j] = i+j;
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

        std::cout << "Mouse clicked\n";

        buttons = SDL_GetMouseState(&mouseX, &mouseY);
        int mouseIndexX = mouseX / tileSize;
        int mouseIndexY = mouseY / tileSize;
        int temp = CheckTiles(mouseIndexX, mouseIndexY);  
        AddTile(mouseIndexX, mouseIndexY, 0);
        canCheck = true;   
    }                   
}

int LevelEditor::CheckTiles(int mX, int mY){


    int mouseX = mX;
    int mouseY = mY;

    int tileValue = 0;

    for(int x = -1; x <= 1; x++) {
        //std::cout << "Here x\n";
        for(int y = -1; y <= 1; y++) {
            //std::cout << "Here y\n";
            if( !(x == 0 && y == 0) &&
                (mouseX - x != -1) && (mouseX + x != (xTiles)) &&
                (mouseY - y != -1) && (mouseY + y != (yTiles))) {
                    //std::cout << "About to check tile\n";
                if(tileMap[mouseY + y][mouseX + x] != 0){

                    //std::cout << "Tile: " << mX + x << " , " << mY + y << " has been checked\n";
                    //tileValue++;
                    //tileValue << 1;
                }
            }
        }
    }
    

    return 1;
};

void LevelEditor::AddTile(int xIndex, int yIndex, int tileValue){

    std::cout << "Adding tile\n";

    int srcX = 0;
    int srcY = 0;

    int destX = 100;
    int destY = 100;

    auto& tile(EntityList->addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, destX, destY, "../art/maps/tilemapdemo.png");
    //tile.addComponent<ColliderComponent>("tile",tileSize, tileSize);
    /*
    for(int x = -1; x <= 1; x++) {

        for(int y = -1; y <= 1; y++) {

            if((x != 0 || y != 0) &&
            (xIndex - x != -1) && (xIndex + x != mapWidth / tileSize) &&
            (yIndex - y != -1) && (yIndex + y != mapHeight / tileSize)) {
                
                if(tileMap[y][x] != 0){
                    // update tile
                }
            }
        }
    }
    */
};

//void LevelEditor::UpdateTile(int xIndex, int yIndex){};

void LevelEditor::SaveLevel(){};

void LevelEditor::LoadLevel(){};