#include "gamestate.hpp"
#include "game.hpp"
#include "init.hpp"
#include "inp.hpp"
#include "macros.hpp"
#include "piece.hpp"
#include "render.hpp"

static const int DELAY = 1000/144;

void GameState::run(){

    if(!init())
        DEBUG_PRINT("Coudlnt init");
    else{


            SDL_Event e;
            bool quit = false;

            while(!quit){

                // to fix the frame rate to 144 fps
                Uint32 startFrame = SDL_GetTicks();
                if(!handleEvent(e)){
                    quit = true;
                    running = false;
                    break;
                }

                updateLogic();
                render();

                Uint32 frameTime = SDL_GetTicks()-startFrame;
                if( frameTime < DELAY )
                    SDL_Delay(DELAY-frameTime);
            }
    }
}

bool GameState::getState(){
    return running;
}

void GameState::reset(){
    SDL_RenderClear( gRenderer );
    for(auto row = GameLogic::getGameMatrix().begin(); row!= GameLogic::getGameMatrix().end(); row++ ){
        for(auto col = row->begin(); col!=row->end(); col++){
            *col = 0;
        }
    }
}

void GameState::free(){

    SDL_DestroyWindow( gWindow );
    SDL_DestroyRenderer( gRenderer );
    gWindow = nullptr;
    gRenderer = nullptr;


}

