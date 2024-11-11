#include <vector>

// similar to game.hpp
// making everything static made this project really simple, not best practice - i know

class Piece{

    public:
        static void spawnTetromino();
        static void moveLeft();
        static void  moveRight();
        static void  moveDown();
        static void  lockPiece( std::vector<std::pair<int, int>>& );
        static std::vector<std::pair<int, int>> getRelativePos( std::vector<std::pair<int, int>>& p);
        static std::pair<int, int> subFromCenter( std::pair<int,int> pos, std::pair<int,int> twoPos);
        static void Rotate( bool direction );
        static bool AbleRotate( std::vector<std::pair<int,int>> modGlobalPos );

        static int tetrominoType;

    
    private:
        int mVel = 50;


};
