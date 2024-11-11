#pragma once

#include <SDL.h>
#include <vector>
#include <list>


// Acts like a singleton, but I liked this syntax more 
// I wouldn't normally impliment singleton-like structures 
// however this project is not large-scale so it was easy to be able
// to access the game logic globally

class GameLogic{

    public:
        GameLogic();

        // gets a refrence to the matrix rather than returning the whole matrix
        static std::vector<std::vector<int>>& getGameMatrix();
        static void rotate( bool direction, bool shouldOffset);
        static void offset( int oldRotIndex, int newRotIndex);
        static int mod( int x, int m); 
        static void clearFullRows();
        static std::vector<std::pair<int, int>> getTetrominoPositions();
        static bool canMoveDown(const std::vector<std::pair<int, int>>& positions);
        static bool canMoveLeft(const std::vector<std::pair<int, int>>& positions);
        static bool canMoveRight(const std::vector<std::pair<int, int>>& positions);


        const static std::vector<  std::vector<std::vector<int>>  > mRotations;
        const static std::vector<  std::vector<std::vector<int>>  > mJLSTZ_Offsets;
        const static std::vector<  std::vector<std::vector<int>>  > mO_Offsets;
        const static std::vector<  std::vector<std::vector<int>>  > mI_Offsets;
        const static std::vector<  std::vector<std::vector<int>>  > mMatrices;


    private:
        static std::vector<std::vector<int>> mGameMatrix;
        int mVel;
};

void updateLogic();
