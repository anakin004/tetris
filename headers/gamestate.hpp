#pragma once

#include <SDL.h>

class GameState{

    public:

        GameState(){
            running = true;
        }

        void run();

        static void reset();

        bool getState();

        ~GameState(){
            free();
        }

        void free();

    private:

        bool running;

};

extern SDL_Window* gWindow;
