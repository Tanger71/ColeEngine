#include "EntityFactory.h"
#include "ECS/Components.h"
#include "Game.h"

EntityFactory::EntityFactory(){
    white = {255, 255, 255, 255}; // TODO: lift scope

}

void EntityFactory::initPlayer(Entity* e, float xpos, float ypos, std::string label){
    e->addGroup(Game::groupPlayers);

    e->addComponent<TransformComponent>(xpos, ypos, 32, 32, 2.0f);

    e->addComponent<SpriteComponent>("player", "Idle", Animation(5, 10, 10));
    e->getComponent<SpriteComponent>().addAnimation("Walk", Animation(7, 10, 10));

    e->addComponent<RectangleColliderComponent>("player", 16, 0, 32, 64);

    e->addComponent<PlayerController>();

    e->addComponent<LabelComponent>(0, -20, label, "entity-arial", white);
}

void EntityFactory::initWorm(Entity* e, float xpos, float ypos, std::string label){
    e->addGroup(Game::groupEnemies);

    e->addComponent<TransformComponent>(xpos, ypos, 32, 32, 2.0f);

    e->addComponent<SpriteComponent>("worm", "Out", Animation(2, 1, 10));
    e->getComponent<SpriteComponent>().addAnimation("Hiding", Animation(2, 8, 5));
    e->getComponent<SpriteComponent>().addAnimation("In", Animation(1, 1, 30));
    e->getComponent<SpriteComponent>().addAnimation("Emerging", Animation(1, 8, 5));

    e->addComponent<RectangleColliderComponent>("worm", 0, 0, 64, 64);
    e->addComponent<CircleColliderComponent>("worm", 32, 32, 200);

    e->addComponent<WormFSM>();

    e->addComponent<LabelComponent>(0, -20, label, "entity-arial", white);
}