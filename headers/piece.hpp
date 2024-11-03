#include <vector>

class Piece{

    public:
        void static spawnTetromino();
        void static moveLeft();
        void static moveRight();
        void static moveDown();
        void static lockPiece( std::vector<std::pair<int, int>>& );
        static std::vector<std::pair<int, int>> getRelativePos( std::vector<std::pair<int, int>>& p);
        static std::pair<int, int> subFromCenter( std::pair<int,int> pos, std::pair<int,int> twoPos);
        void static Rotate( bool direction );
        bool static AbleRotate( std::vector<std::pair<int,int>> modGlobalPos );

        static int tetrominoType;

    
    private:
        int mVel = 50;


};
