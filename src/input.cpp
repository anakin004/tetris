#include "inp.hpp"
#include "piece.hpp"
#include <stdio.h>

bool handleEvent(SDL_Event e) {
    
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_a:
                    Piece::moveLeft();                                           
                    break;
                case SDLK_d:
                    Piece::moveRight();
                    break;
                case SDLK_s:
                    Piece::moveDown();
                    break;
                case SDLK_m:
                    Piece::Rotate(true);
                    break;
                case SDLK_n:
                    Piece::Rotate(false);
                    break;
                default:

                    break;
            }
        }
    }
    return true;
}