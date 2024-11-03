#include <ctime>
#include <random>
#include <algorithm>
#include "gamestate.hpp"
#include "macros.hpp"
#include "piece.hpp"
#include "game.hpp"


int Piece::tetrominoType = -1;

void Piece::spawnTetromino() {
    // Seed for random selection (do this once in your main function)
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Randomly select a Tetromino (assuming 5 types)
    tetrominoType = std::rand() % 5;
    
    // Assuming Tetromino is placed at the top center of the matrix

    int startX = std::rand()%7; /*matrix width is 10*/  // Adjust based on your Tetromino size
    int startY = 0;

    // Place the selected Tetromino on the game matrix
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if( GameLogic::getGameMatrix()[startY + y][startX + x] != 0){
                GameState::reset();
                return;
            }
            if (GameLogic::mMatrices[tetrominoType][y][x] !=0 ) {
                GameLogic::getGameMatrix()[startY + y][startX + x] = GameLogic::mMatrices[tetrominoType][y][x];
            }
        }
    }
}

void Piece::moveDown(){

    std::vector<std::pair<int, int>> positions = GameLogic::getTetrominoPositions();

    if ( GameLogic::canMoveDown(positions)){
        std::pair<int,int> twoPos;
        // make function to get active tetromino position
        for( const auto it: positions){
            if(GameLogic::getGameMatrix()[it.first][it.second] == 2){
                twoPos.first = it.first; twoPos.second = it.second;
            }
            GameLogic::getGameMatrix()[it.first][it.second] = 0;

        }
        for( const auto it: positions){
            if(it.first == twoPos.first && it.second == twoPos.second)
                GameLogic::getGameMatrix()[it.first+1][it.second] = 2;
            else
                GameLogic::getGameMatrix()[it.first+1][it.second] = 1;

        }
    }


}


void Piece::moveRight(){
    std::vector<std::pair<int, int>> positions = GameLogic::getTetrominoPositions();
    
    if( GameLogic::canMoveRight(positions) ){
        std::pair<int,int> twoPos;

        for( const auto it: positions){
            if(GameLogic::getGameMatrix()[it.first][it.second] == 2){
                twoPos.first = it.first; twoPos.second = it.second;
            }
            GameLogic::getGameMatrix()[it.first][it.second] = 0;

        }
        for( const auto it: positions){
            if(it.first == twoPos.first && it.second == twoPos.second)
                GameLogic::getGameMatrix()[it.first][it.second+1] = 2;
            else
                GameLogic::getGameMatrix()[it.first][it.second+1] = 1;

        }

    }   


}


void Piece::moveLeft(){

    std::vector<std::pair<int, int>> positions = GameLogic::getTetrominoPositions();
    
    if( GameLogic::canMoveLeft(positions) ){
        std::pair<int,int> twoPos;

        for( const auto it: positions){
            if(GameLogic::getGameMatrix()[it.first][it.second] == 2){
                twoPos.first = it.first; twoPos.second = it.second;
            }
            GameLogic::getGameMatrix()[it.first][it.second] = 0;

        }
        for( const auto it: positions){
            if(it.first == twoPos.first && it.second == twoPos.second)
                GameLogic::getGameMatrix()[it.first][it.second-1] = 2;
            else
                GameLogic::getGameMatrix()[it.first][it.second-1] = 1;

        }

    }   


}

void Piece::lockPiece( std::vector<std::pair<int, int>>& p){
    int tetrominoVal = tetrominoType+5;

    // tetromino val is +5 so when we determine its color we use mod
    for(auto pair : p){
        GameLogic::getGameMatrix()[pair.first][pair.second]=tetrominoVal;
    }

}


std::vector<std::pair<int, int>> Piece::getRelativePos( std::vector<std::pair<int, int>>& p){

    std::vector<std::pair<int, int>> relative(p.size());
    std::pair<int,int> twoPos;

    //finding two pos for the center or rotation
    for(auto it : p){
        if(GameLogic::getGameMatrix()[it.first][it.second]==2){
            twoPos.first = it.first; twoPos.second = it.second;
            break;
        }
    }

    std::transform(p.begin(), p.end(), relative.begin(), [&](const std::pair<int, int>& pos) {
            return subFromCenter(pos, twoPos);
        });


    return relative;

}

std::pair<int, int> Piece::subFromCenter( std::pair<int,int> pos, std::pair<int,int> twoPos){
    // keep in mind in sdl the coodinate plane is flipped
    return { pos.first - twoPos.first , pos.second - twoPos.second };
}

void Piece::Rotate( bool direction){
    
    std::vector<std::pair<int, int>> globalPos = GameLogic::getTetrominoPositions();

    std::pair<int,int> twoPos;

    //finding two pos for the center or rotation
    for(auto it : globalPos){
        if(GameLogic::getGameMatrix()[it.first][it.second]==2){
            twoPos.first = it.first; twoPos.second = it.second;
            break;
        }
    }

    std::vector<std::pair<int, int>> relativePos = Piece::getRelativePos( globalPos );
    std::vector<std::vector<int>> rotMatrix;

    // if true we rotate clockwise
    if( direction == true )
        rotMatrix = GameLogic::mRotations[0];
    else
        rotMatrix = GameLogic::mRotations[1];

    for( auto it = relativePos.begin(); it!=relativePos.end(); it++ ){
        int y = it->first;
        int x = it->second;

        it->first = rotMatrix[0][0]*y + rotMatrix[0][1]*x;
        it->second = rotMatrix[1][0]*y + rotMatrix[1][1]*x;


    }

 
    for (size_t i = 0; i < globalPos.size(); ++i) {
        int newRow = twoPos.first + relativePos[i].first;
        int newCol = twoPos.second + relativePos[i].second;        
        if (newRow >= 20 || newRow < 0 || newCol >= 10 || newCol < 0 || GameLogic::getGameMatrix()[newRow][newCol] > 2) {
            return;
        }
    }

    for (const auto& pos : globalPos) {
        GameLogic::getGameMatrix()[pos.first][pos.second] = 0;
    }

    for (size_t i = 0; i < globalPos.size(); ++i) {
        int newRow = twoPos.first + relativePos[i].first;
        int newCol = twoPos.second + relativePos[i].second;
        GameLogic::getGameMatrix()[newRow][newCol] = (relativePos[i].first == 0 && relativePos[i].second == 0) ? 2 : 1;

    }



}

