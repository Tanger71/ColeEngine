#include <iostream>
#include "Game.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "Animation.h"
#include "ECS/FSM/FSMs.h"
#include <sstream>

int Game::frameCnt = 0;
Uint32 lastFrame = 0;

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 800, 640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity()); //TODO: learn this IMP... what is this syntax?
auto& label(manager.addEntity());
auto& worm(manager.addEntity());

Game::Game() = default;
Game::~Game() = default;

void Game::throwErr(const std::string& e) {
    std::cout << "Error: " << e << std::endl;
}

void Game::init(const char* title, int width, int height, bool fullscreen) {

    int flags = 0;
    if(fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Game: Subsystems Initialised!..." << std::endl;

        window = SDL_CreateWindow(title, /*SDL_WINDOWPOS_CENTERED*/0, /*SDL_WINDOWPOS_CENTERED*/20, width, height, flags);
        if(window){
            std::cout << "Game: Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1 , 0 );
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Game: Renderer created!" << std::endl;
        }

        isRunning = true;
    }

    if(TTF_Init() == -1){
        Game::throwErr("SDL_TTF");
    }

    assets->addTexture("terrain", "assets/terrain_ss.png");
    assets->addTexture("player", "assets/rogue.png");
    assets->addTexture("projectile", "assets/proj.png");
    assets->addTexture("worm", "assets/worm.png");

    assets->addFont("arial", "assets/Arial.ttf", 24);

    map = new Map("terrain", 3, 32);

    map->LoadMap("assets/map.gmap", 25, 20);

    //ecs implementation
    player.addComponent<TransformComponent>(800.0f, 640.0f, 32, 32, 2.0f);
    player.addComponent<SpriteComponent>("player", "Idle", Animation(5, 10, 10));
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    player.getComponent<SpriteComponent>().addAnimation("Walk", Animation(7, 10, 10));

    worm.addComponent<TransformComponent>(1000.f, 640.f, 32, 32, 2.0f);
    worm.addComponent<SpriteComponent>("worm", "Out", Animation(2, 2, 10));
    worm.addComponent<ColliderComponent>("worm0");
    worm.getComponent<SpriteComponent>().addAnimation("Hiding", Animation(2, 8, 5));
    worm.getComponent<SpriteComponent>().addAnimation("In", Animation(1, 1, 30));
    worm.getComponent<SpriteComponent>().addAnimation("Emerging", Animation(1, 8, 5));
    worm.addComponent<WormFSM>();
    worm.addGroup(groupEnemies);

    SDL_Color white = {255, 255, 255, 255};
    label.addComponent<UILabel>(10, 10, "Test_String", "arial", white);

    assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
    assets->CreateProjectile(Vector2D(600, 620), Vector2D(2, 0), 200, 2, "projectile");
    assets->CreateProjectile(Vector2D(400, 600), Vector2D(2, 1), 200, 2, "projectile");
    assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, -1), 200, 2, "projectile");

    std::cout << "Game: Ready!" << std::endl;
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents() {
    
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Game::update() {
    Game::frameCnt++;

    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;

    std::stringstream ss;

    ss << "FPS: " << 1000*1.0f/static_cast<float>(SDL_GetTicks() - lastFrame); //Frames/time = fps
    label.getComponent<UILabel>().setLabelText(ss.str(), "arial");

    for (auto& c : colliders) {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol)) {
            player.getComponent<TransformComponent>().position = playerPos;
        }
    }

    for (auto& p : projectiles) {
        if (Collision::AABB(player.getComponent<ColliderComponent>(), p->getComponent<ColliderComponent>())) {
            std::cout << "hit player" << std::endl;
            p->destroy();
        }
    }

    // update entities
    manager.refresh();
    manager.update();

    // update camera to player
    camera.x = player.getComponent<TransformComponent>().position.x - 400.0f;
    camera.y = player.getComponent<TransformComponent>().position.y - 320.0f;

    //for camera bounds
    //if (camera.x < 0) camera.x = 0;
    //if (camera.y < 0) camera.y = 0;
   //if (camera.x > camera.w) camera.x = camera.w;
    //if (camera.y > camera.h) camera.y = camera.h;

    lastFrame = SDL_GetTicks();
}

void Game::render() {
    SDL_RenderClear(renderer);
    for (auto& t : tiles) {
        t->draw();
    }
    for (auto& c : colliders) {
        c->draw();
    }
    for (auto& p : players) {
        p->draw();
    }
    for (auto& e : enemies) {
        e->draw();
    }
    for (auto& p : projectiles) {
        p->draw();
    }
    label.draw();

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned!" << std::endl;
}
