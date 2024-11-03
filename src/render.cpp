#include "render.hpp"
#include "game.hpp"
#include "piece.hpp"
#include "macros.hpp"



/*
    the matrix will have a 0's,1's,2's, etc to represent the type
    of tetromino and color
    the sColors matrix have rgb values according to the number
*/
const static std::vector<std::vector<Uint8>> sColors = {
    {0,255,0},
    {255,255,0},
    {255,0,0},
    {0,0,255},
    {255,192,203}
};


void renderMatrix( const std::vector<std::vector<int>> &matrix ){

    // iterating over rows in the matrix
   for (int y = 0; y < MATRIX_HEIGHT; ++y) {
    for (int x = 0; x < MATRIX_WIDTH; ++x) {

        int matrixVal = matrix[y][x];
        DEBUG_PRINT("%d",matrixVal);
        if (matrixVal == 0) {
            continue; // Skip rendering if the value is 0
        }

        /* 
           Assuming sColors is a 2D array or vector of RGB values
           we grab sColors[*col-1] since the indexing starts at 0 and we are ignoring the 0's
           in the matrix
        */

       //setting draw color to the tetromino color

        if(matrixVal == 1 || matrixVal == 2)
            SDL_SetRenderDrawColor(gRenderer, sColors[Piece::tetrominoType%5][0], sColors[Piece::tetrominoType][1], sColors[Piece::tetrominoType][2], 255); 

        else
            SDL_SetRenderDrawColor(gRenderer, sColors[matrixVal%5][0], sColors[matrixVal%5][1], sColors[matrixVal%5][2], 255); // Set color based on *col

        // Define the rectangle to render
        SDL_Rect rect = { x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE };
        SDL_RenderDrawRect( gRenderer, &rect);

        // Render the filled rectangle
        SDL_RenderFillRect(gRenderer, &rect);


        }
        DEBUG_PRINT("\n");  
    }
    DEBUG_PRINT("\n");

}

void render(){
    
    const auto matrix = static_cast<const std::vector<std::vector<int>>
                        >(GameLogic::getGameMatrix());
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
    SDL_RenderClear(gRenderer);
    renderMatrix(matrix);
    SDL_RenderPresent(gRenderer);


}