#include "game.hpp"
#include "render.hpp"
#include "piece.hpp"
#include "macros.hpp"


const int CELL_SIZE = 50;
const int MATRIX_WIDTH = 10;
const int MATRIX_HEIGHT = 20;


GameLogic::GameLogic()
{
    mVel = 50;

}


std::vector<std::vector<int>>& GameLogic::getGameMatrix() {
    return mGameMatrix;
}

const std::vector<std::vector<std::vector<int>>> GameLogic::mMatrices = {
    // I piece
    { 
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 2, 0, 0},
        {0, 1, 0, 0}
    },
    // L piece
    { 
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {2, 1, 0, 0},
        {0, 0, 0 ,0}
    },
    // Z piece
    { 
        {0, 0, 1, 1},
        {0, 0, 2, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    // T piece
    { 
        {0, 1, 0, 0},
        {1, 2, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // O piece
    { 
        {1, 1, 0, 0},
        {1, 2, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};



const std::vector<std::vector<std::vector<int>>> GameLogic::mJLSTZ_Offsets = {
    {
        {0,0},
        {0,0},
        {0,0},
        {0,0},
    },
    {
        {0,0},
        {1,0},
        {0,0},
        {-1,0},
    },
    {
        {0,0},
        {1,-1},
        {0,0},
        {-1,-1},
    },
    {
        {0,0},
        {0,2},
        {0,0},
        {0,2},
    },
    {
        {0,0},
        {1,2},
        {0,0},
        {1,-2},
    }
};

const std::vector<std::vector<std::vector<int>>> GameLogic::mO_Offsets = {
    {
        {0,0},
        {0,-1},
        {-1,-1},
        {-1,0},
    },
};

const std::vector<std::vector<std::vector<int>>> GameLogic::mI_Offsets = {
    {
        {0,0},
        {-1,0},
        {-1,1},
        {0,1},
    },
    {
        {-1,0},
        {0,0},
        {1,1},
        {0,1},
    },
    {
        {2,0},
        {0,0},
        {-2,1},
        {0,1},
    },
    {
        {-1,0},
        {0,1},
        {1,0},
        {0,-1},
    },
    {
        {2,0},
        {0,2},
        {-2,0},
        {0,2},
    }
};


const std::vector<std::vector<std::vector<int>>>GameLogic::mRotations={

    //clockwise rotation
    {
     { 0, 1,},
     {-1, 0,},
    },

    //counter-clockwise rotation
    {
     { 0, -1,},
     { 1, 0,},
    }

};



// static members have to be initalized outside of the class
std::vector<std::vector<int>> GameLogic::mGameMatrix(MATRIX_HEIGHT, std::vector<int>(MATRIX_WIDTH, 0));



int mod( int x, int m){
    return (x % m + m) % m;
}


//direction - true(clockwise) false(counter)
void GameLogic::rotate(bool direction, bool shouldOffset) {
}



void GameLogic::clearFullRows() {
    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
        bool isFullRow = true;
        for (int x = 0; x < MATRIX_WIDTH; ++x) {
            if (mGameMatrix[y][x] == 0) {
                isFullRow = false;
                break;
            }
        }
        if (isFullRow) {
            // Clear the row
            for (int x = 0; x < MATRIX_WIDTH; ++x) {
                mGameMatrix[y][x] = 0;
            }
            // Shift down all rows above the cleared row
            for (int row = y; row > 0; --row) {
                for (int col = 0; col < MATRIX_WIDTH; ++col) {
                    mGameMatrix[row][col] = mGameMatrix[row - 1][col];
                }
            }
            // Clear the top row after shifting
            for (int col = 0; col < MATRIX_WIDTH; ++col) {
                mGameMatrix[0][col] = 0;
            }
        }
    }
}

std::vector<std::pair<int, int>> GameLogic::getTetrominoPositions() {
    std::vector<std::pair<int, int>> positions;
    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
        for (int x = 0; x < MATRIX_WIDTH; ++x) {
            if (mGameMatrix[y][x] == 1 || mGameMatrix[y][x] == 2) {
                positions.push_back({y, x});
            }
        }
    }

    // if no tetromino we spawn and get the position
    if(positions.empty()){
        Piece::spawnTetromino();
        GameLogic::getTetrominoPositions();
    }
    return positions;
}


bool GameLogic::canMoveDown(const std::vector<std::pair<int, int>>& positions) {
    for (const auto& pos : positions) {
        int newY = pos.first + 1;
        if (newY >= MATRIX_HEIGHT || mGameMatrix[newY][pos.second] > 2 ) {
            return false;
        }
    }
    return true;
}

bool GameLogic::canMoveLeft(const std::vector<std::pair<int, int>>& positions) {
    for (const auto& pos : positions) {
        int newX = pos.second - 1;
        if (newX < 0 || mGameMatrix[pos.first][newX] > 2 ) {
            return false;
        }
    }
    return true;
}

bool GameLogic::canMoveRight(const std::vector<std::pair<int, int>>& positions) {
    for (const auto& pos : positions) {
        int newX = pos.second + 1;
        if (newX >= MATRIX_WIDTH || mGameMatrix[pos.first][newX] > 2 ) {
            return false;
        }
    }
    return true;
}

void updateLogic(){
    static int frames=0;
    if (frames%144==0){

        Piece::moveDown();
        std::vector<std::pair<int, int>> Pairs = GameLogic::getTetrominoPositions();

        if( !GameLogic::canMoveDown(Pairs)){
            Piece::lockPiece(Pairs);
            GameLogic::clearFullRows();
        }

    }
    frames+=1;
}


