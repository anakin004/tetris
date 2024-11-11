#pragma once

#include <SDL.h>

class GameState{

    public:

        GameState() : running(true) {
        }
        ~GameState(){
            free();
        }

        void run();
        static void reset();
        bool getState();
        void free();

    private:

        bool running;

};

extern SDL_Window* gWindow;
