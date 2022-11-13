//
// Created by Sawyer Tang on 11/13/22.
//

#ifndef TUT1_GAME_H
#define TUT1_GAME_H
#include "SDL.h"
#include <stdio.h>

class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    bool running() { return isRunning; }
    void render();
    void clean();


private:
    int cnt = 0;
    bool isRunning = false;
    SDL_Window *window;
    SDL_Renderer *renderer;
};


#endif //TUT1_GAME_H
