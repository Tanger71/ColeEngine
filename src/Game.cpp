//
// Created by Sawyer Tang on 11/13/22.
//

#include <iostream>
#include "Game.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 800, 640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity()); //TODO: learn this IMP... what is this syntax?
auto& label(manager.addEntity());

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int width, int height, bool fullscreen) {

    int flags = 0;
    if(fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Game: Subsystems Initialised!..." << std::endl;

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
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
        std::cout << "Error: SDL_TTF" << std::endl;
    }

    assets->addTexture("terrain", "assets/terrain_ss.png");
    assets->addTexture("player", "assets/rogue.png");
    assets->addTexture("projectile", "assets/proj.png");

    assets->addFont("arial", "assets/Arial.ttf", 24);

    map = new Map("terrain", 3, 32);

    map->LoadMap("assets/map.gmap", 25, 20);

    //ecs implementation
    player.addComponent<TransformComponent>(800.0f, 640.0f, 32, 32, 2);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

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

    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;

    std::stringstream ss;

    ss << "Player position: " << playerPos;
    label.getComponent<UILabel>().setLabelText(ss.str(), "arial");

    manager.refresh();
    manager.update();

    for (auto& c : colliders) {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol)) {
            player.getComponent<TransformComponent>().position = playerPos;
        }
    }

    for (auto& p : projectiles) {
        if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider)) {
            std::cout << "hit player" << std::endl;
            p->destroy();
        }
    }

    // update camera to player
    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;

    //for camera bounds
    //if (camera.x < 0) camera.x = 0;
    //if (camera.y < 0) camera.y = 0;
    //if (camera.x > camera.w) camera.x = camera.w;
    //if (camera.y > camera.h) camera.y = camera.h;

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
