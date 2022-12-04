#include <iostream>
#include "Game.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "EntityFactory.h"
#include <sstream>

bool Game::debugGame = true;
int Game::frameCnt = 0;
Uint32 lastFrame = 0;

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 800, 640 };

AssetManager* Game::assets = new AssetManager(&manager);

EntityFactory* Game::entityFactory = new EntityFactory(&manager);

bool Game::isRunning = false;

Entity* player;
auto& label(manager.addEntity());

std::map<std::string, Entity*> entities; //mby make for all entities ...

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
//    assets->addTexture("stone", "assets/stone_proj.png");

    assets->addFont("arial", "assets/Arial.ttf", 24);
    assets->addFont("entity-arial", "assets/Arial.ttf", 10);

    map = new Map("terrain", 3, 32);

    map->LoadMap("assets/map.gmap", 25, 20);

    player = entityFactory->mintPlayer(Vector2D(800.0f, 640.0f), "player");
    entities.emplace("worm0", entityFactory->mintWorm(Vector2D(1000.f, 640.f), "worm0"));
    entities.emplace("worm1", entityFactory->mintWorm(Vector2D(800.f, 800.f), "worm1"));

    SDL_Color white = {255, 255, 255, 255};
    label.addComponent<LabelComponent>(10, 10, "Test_String", "arial", white);

    entityFactory->mintProjectile(Vector2D(600, 600), Vector2D(1, 0), 200, 2, "projectile", "proj0");
    entityFactory->mintProjectile(Vector2D(600, 620), Vector2D(1, 0), 200, 1, "projectile", "proj1");
    entityFactory->mintProjectile(Vector2D(400, 600), Vector2D(6, 1), 200, 2, "projectile", "proj2");
    entityFactory->mintProjectile(Vector2D(600, 600), Vector2D(2, -1), 200, 2, "projectile", "proj3");

    std::cout << "Game: Ready!" << std::endl;
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& walls(manager.getGroup(Game::groupWall));
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

    RectangleColliderComponent* playerCol = &player->getComponent<RectangleColliderComponent>();
    CircleColliderComponent* worm0CirCol = &entities["worm0"]->getComponent<CircleColliderComponent>();
    CircleColliderComponent* worm1CirCol = &entities["worm1"]->getComponent<CircleColliderComponent>();
    Vector2D playerPos = player->getComponent<TransformComponent>().position;

    std::stringstream ss;

//    std::cout << "FPS: " << 1000*1.0f/static_cast<float>(SDL_GetTicks() - lastFrame) << std::endl; //Frames/time = fps

    ss << "FPS: " << 1000*1.0f/static_cast<float>(SDL_GetTicks() - lastFrame); //Frames/time = fps
    label.getComponent<LabelComponent>().setLabelText(ss.str(), "arial");

    if (Collision::CircleRectangle(*worm0CirCol, *playerCol)) {
        entities["worm0"]->getComponent<RectangleColliderComponent>().addCollision(Game::groupPlayers);
        entities["worm0"]->getComponent<CircleColliderComponent>().addCollision(Game::groupPlayers);
    }
    if (Collision::CircleRectangle(*worm1CirCol, *playerCol)) {
        entities["worm1"]->getComponent<RectangleColliderComponent>().addCollision(Game::groupPlayers);
        entities["worm1"]->getComponent<CircleColliderComponent>().addCollision(Game::groupPlayers);
    }

    // update entities
    manager.refresh();
    manager.update();

    // resolve collisions
    for (auto& c : walls) {
        RectangleColliderComponent cCol = c->getComponent<RectangleColliderComponent>();
        if (Collision::AABB(cCol, *playerCol)) {
            player->getComponent<TransformComponent>().position = playerPos;
        }
    }
    for (auto& p : projectiles) {
        CircleColliderComponent cc = p->getComponent<CircleColliderComponent>();
        if (cc.tag != "playerBolt" && Collision::CircleRectangle(cc, player->getComponent<RectangleColliderComponent>())) {
            std::cout << "hit player" << std::endl;
            p->destroy();
        }
    }

    // update camera to player
    camera.x = player->getComponent<TransformComponent>().position.x - 400.0f;
    camera.y = player->getComponent<TransformComponent>().position.y - 320.0f;

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
    for (auto& c : walls) {
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned!" << std::endl;
}
