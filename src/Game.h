#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "EntityFactory.h"

class AssetManager; // TODO: Why tho... https://stackoverflow.com/questions/23283080/compiler-error-c4430-missing-type-specifier-int-assumed

/**
 * @brief Game Instance.
 *
 * @author sawyercoletang
 *
 * @note currently being used as a sandbox for development of engine
 */
class Game {

public:
    Game();
    ~Game();

    /**
     * @brief throw error to console.
     *
     * @param e error string
     */
    static void throwErr(const std::string& e);

    /**
     * @brief to initialize the Game instance.
     * @param title of the game window
     * @param width of the game window
     * @param height of the game window
     * @param fullscreen or not
     */
    void init(const char* title, int width, int height, bool fullscreen);

    /**
     * @brief handle game-events
     */
    void handleEvents();

    /**
     * @brief update game-objects
     */
    void update();

    /**
     * @brief returns true if game is running
     * @returns true when game is running
     */
    bool running() { return isRunning; }

    /**
     * @brief render game-objects
     */
    void render();

    /**
     * @brief clean game instance
     */
    void clean();

    static int frameCnt;
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_Rect camera;
    static AssetManager* assets;
    static EntityFactory* entityFactory;

    static bool debugGame;

    enum groupLabels : std::size_t {
        groupMap,
        groupPlayers,
        groupEnemies,
        groupWall,
        groupProjectiles,
        groupPlayerProjectiles,
        groupDebug
    };

private:
    int cnt = 0;
    SDL_Window *window;
};
