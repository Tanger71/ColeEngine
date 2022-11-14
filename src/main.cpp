//
// Created by Sawyer Tang on 11/12/22.
//

#include "SDL.h"
#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[]) {
//#ifdef __clang_major__
//    printf ("clang detected version %d.%d\n", __clang_major__, __clang_minor__);
//#endif
//
//#ifdef __GNUC__
//    // note that clang 3.7 declares itself as a gcc 4.2"
//    printf ("gcc detected version %d.%d\n", __GNUC__, __GNUC_MINOR__);
//#endif

    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("ColeEngine", 800, 640, false);

    while(game->running()){
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay-frameTime);
        }
    }

    game->clean();
    return 0;
}