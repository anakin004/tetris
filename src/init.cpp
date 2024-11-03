#include "init.hpp"
#include "macros.hpp"
#include <iostream>

// Global variables
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

const int WIDTH = 500;
const int HEIGHT = 1000;


bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0) {
        success = false;
        DEBUG_PRINT("Couldn't initialize video");
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            DEBUG_PRINT("Warning: Linear texture filtering not enabled!");
        }
        gWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                                   SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            success = false;
            DEBUG_PRINT("Could not create window %s", SDL_GetError());
        } else {
            if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG  ) {
                success = false;
                DEBUG_PRINT(" wrong goofy ");
            } else {
                gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
                if (gRenderer == NULL) {
                    DEBUG_PRINT("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                    success = false;
                } else{
                    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                    
                    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                    {
                        DEBUG_PRINT( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                        success = false;
                    }
    

                }
            }
        }
    }
    return success;
}
