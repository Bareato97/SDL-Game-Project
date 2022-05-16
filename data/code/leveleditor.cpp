#include "leveleditor.hpp"
#include "game.hpp"




LevelEditor::LevelEditor(int mWidth, int mHeight, int tSize, float scale){

    InitialiseIndexMap();

    tileSetPaths = "data/art/maps/tilemapdemo.png";

    

    mapWidth = mWidth;
    mapHeight = mHeight;
    tileSize = tSize;
    tileScale = scale;

    yTiles = mapHeight/(int)(tileSize*tileScale);
    xTiles = mapWidth/(int)(tileSize*tileScale);

    tileMap = new std::pair<int,int>*[yTiles];
    for(int i = 0; i < yTiles; i++){

        tileMap[i] = new std::pair<int,int>[xTiles];
        for(int j = 0; j < xTiles; j++){

            tileMap[i][j].first = 0;
            tileMap[i][j].second = 0;
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

void LevelEditor::update(int mouseX, int mouseY, Uint32 button){

    if(canCheck == true){

        canCheck = false;
        int mouseIndexX = mouseX / (int)(tileSize*tileScale);
        int mouseIndexY = mouseY / (int)(tileSize*tileScale);
        sameTile = ((mouseIndexX == prevMouseX) && (mouseIndexY == prevMouseY));
        if(!(mouseIndexX >= xTiles || mouseIndexY >= yTiles || mouseIndexX < 0 || mouseIndexY < 0)){

                switch (button)
            {
            case 1:
                if(sameTile == false || (prevButton != button)){ // Prevent repeated calls on same tile, allow for hold down drawing
                    if(tileMap[mouseIndexY][mouseIndexX].second == 0 || tileMap[mouseIndexY][mouseIndexX].first != tileType){

                        tileMap[mouseIndexY][mouseIndexX].first = tileType;
                        tileMap[mouseIndexY][mouseIndexX].second = tileIndex[CheckTiles(mouseIndexX, mouseIndexY, tileType)];
                        UpdateNearbyTiles(mouseIndexX, mouseIndexY, tileType);
                        updateTexture();
                        prevMouseX = mouseIndexX;
                        prevMouseY = mouseIndexY;
                        prevButton = button;
                    }
                }
                break;
            case 4:
                if(sameTile == false || (prevButton != button)){ // Prevent repeated calls on same tile, allow for hold down drawing
                if(tileMap[mouseIndexY][mouseIndexX].second != 0){

                        RemoveTile(mouseIndexX, mouseIndexY);
                        UpdateNearbyTiles(mouseIndexX, mouseIndexY, tileType);
                        updateTexture();
                        prevMouseX = mouseIndexX;
                        prevMouseY = mouseIndexY;
                        prevButton = button;
                }
                }
                break;
            default:
                break;
            }              
        }   

        canCheck = true;         
    }  
}

int LevelEditor::CheckTiles(int mX, int mY, int tType){


    int mouseX = mX;
    int mouseY = mY;

    int tileValue = 0u;
    
    for(int y = -1; y <= 1; y++) {

        for(int x = -1; x <= 1; x++) {

            if( !(x == 0 && y == 0)) { 

                tileValue = tileValue >> 1; // shift right
                if((mouseX + x >= 0) && ((mouseX + x) < xTiles) &&
                   (mouseY + y >= 0) && ((mouseY + y) < yTiles)) {
                    if(tileMap[mouseY + y][mouseX + x].first = tType){
                        if(tileMap[mouseY + y][mouseX + x].second != 0){                      
                            if(x == -1 && y == -1){

                                if(tileMap[mouseY-1][mouseX].second !=0 && tileMap[mouseY][mouseX -1].second !=0){
                                    tileValue+=128;
                                }
                            }
                            else if(x == 1 && y == 1){

                                if(tileMap[mouseY + 1][mouseX].second !=0 && tileMap[mouseY][mouseX + 1].second !=0){
                                    tileValue+=128;
                                }
                            }
                            else if(x == -1 && y == 1){

                                if(tileMap[mouseY][mouseX - 1].second !=0 && tileMap[mouseY + 1][mouseX].second !=0){
                                    tileValue+=128;
                                }
                            }
                            else if(x == 1 && y == -1){

                                if(tileMap[mouseY][mouseX + 1].second !=0 && tileMap[mouseY - 1][mouseX].second !=0){
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
    }
    
    return tileValue;
};

void LevelEditor::RemoveTile(int xIndex, int yIndex){
    
    tileMap[yIndex][xIndex].first = 0;
    tileMap[yIndex][xIndex].second = 0;
    UpdateNearbyTiles(xIndex, yIndex, 0);
};


// Runs a check on the tiles surrounding the coordinates provided
void LevelEditor::UpdateNearbyTiles(int xIndex, int yIndex, int tType){

    for(int x = -1; x <= 1; x++) {

        for(int y = -1; y <= 1; y++) {

            if((x != 0 || y != 0) &&
                ((xIndex + x >= 0) && ((xIndex + x) < xTiles) &&
                 (yIndex + y >= 0) && ((yIndex + y) < yTiles))) {
                
                if(tileMap[yIndex + y][xIndex + x].second != 0){
                    tileMap[yIndex + y][xIndex + x].second = tileIndex[CheckTiles(xIndex + x, yIndex + y, tileMap[yIndex + y][xIndex + x].first)];
                }
            }
        }
    }
};

void LevelEditor::updateTexture(){


    // removes texture from memory
    if(combinedTexture != NULL){
        SDL_DestroyTexture(combinedTexture);
    }
    if(tileMapTexture != NULL){
        SDL_DestroyTexture(tileMapTexture);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"); // prevent pixel interpolation
    // creates texture which can be drawn to
    combinedTexture = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, xTiles*tileSize, yTiles*tileSize);
    // Set texture as render target
    SDL_SetRenderTarget(Game::renderer, combinedTexture);
    // clears the renderer of previous filler
    SDL_RenderClear(Game::renderer); 
    tileMapTexture = TextureManager::LoadTexture(tileSetPaths);
    for (int i = 0; i < xTiles; i++)
    {
        for(int j = 0; j < yTiles; j++)
        {
            if(tileMap[j][i].second != 0){

                srcRect.w = srcRect.h = tileSize;

                // Get source image position from mapped index
                int x = (tileMap[j][i].second % 12) * tileSize;
                int y = (tileMap[j][i].second / 12) * tileSize;
                srcRect.x = x;
                srcRect.y = y;

                desRect.h = desRect.w = tileSize;
                desRect.x = i*tileSize;
                desRect.y = j*tileSize;

                TextureManager::Draw(tileMapTexture, srcRect, desRect);
            }
        }
    }
    
    SDL_SetRenderTarget(Game::renderer, NULL);
}

/*

Currently this is very inefficient for a large static texture.
Need to look into texture targetting, so tilemap can be combined into a single texture to allow for hardware acceleration
Repeated cpu -> gpu calls dont provide much performance options ie for loop > draw call > for loop > draw call > ...

*/
void LevelEditor::DrawLevel(){
    
    srcRect.x = srcRect.y = 0;
    srcRect.w = xTiles * tileSize;
    srcRect.h = yTiles * tileSize;

    desRect.x = -Game::camera.x;
    desRect.y = -Game::camera.y;
    desRect.w = (int)(xTiles * tileSize * tileScale);
    desRect.h = (int)(yTiles * tileSize * tileScale);
    TextureManager::Draw(combinedTexture, srcRect, desRect);
}

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