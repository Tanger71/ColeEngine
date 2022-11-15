//
// Created by Sawyer Tang on 11/13/22.
//

#ifndef TUT1_GAME_H
#define TUT1_GAME_H
#include "SDL.h"
#include "SDL_image.h"
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

    static SDL_Renderer *renderer;
    static SDL_Event event;


private:
    int cnt = 0;
    bool isRunning = false;
    SDL_Window *window;
};


#endif //TUT1_GAME_H
