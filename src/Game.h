//
// Created by Sawyer Tang on 11/13/22.
//

#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>

class ColliderComponent;

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

    static void AddTile(int id, int x, int y);
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent*> colliders;


private:
    int cnt = 0;
    bool isRunning = false;
    SDL_Window *window;
};
