#include "EntityFactory.h"

#include <utility>
#include "ECS/Components.h"
#include "Game.h"

EntityFactory::EntityFactory(Manager* man) : manager(man) {
    white = {255, 255, 255, 255}; // TODO: lift scope
}

Entity* EntityFactory::mintPlayer(Vector2D pos, std::string label){
    auto& e(manager->addEntity()); //TODO: learn this IMP... what is this syntax?
    e.addGroup(Game::groupPlayers);
    e.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 2.0f);
    e.addComponent<SpriteComponent>("player", "Idle", Animation(5, 10, 10));
    e.getComponent<SpriteComponent>().addAnimation("Walk", Animation(7, 10, 10));
    e.addComponent<RectangleColliderComponent>(label, 16, 0, 32, 64);
    e.addComponent<PlayerController>();
    e.addComponent<LabelComponent>(0, -20, label, "entity-arial", white);

    return &e;
}

Entity* EntityFactory::mintWorm(Vector2D pos, std::string label){
    auto& e(manager->addEntity());
    e.addGroup(Game::groupEnemies);
    e.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 2.0f);
    e.addComponent<SpriteComponent>("worm", "Out", Animation(2, 1, 10));
    e.getComponent<SpriteComponent>().addAnimation("Hiding", Animation(2, 8, 5));
    e.getComponent<SpriteComponent>().addAnimation("In", Animation(1, 1, 30));
    e.getComponent<SpriteComponent>().addAnimation("Emerging", Animation(1, 8, 5));
    e.addComponent<RectangleColliderComponent>(label, 0, 0, 64, 64);
    e.addComponent<CircleColliderComponent>(label, 32, 32, 200);
    e.addComponent<WormFSM>();
    e.addComponent<LabelComponent>(0, -20, label, "entity-arial", white);

    return &e;
}

Entity* EntityFactory::mintStoneProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string label) {
    auto& e(manager->addEntity());

    forgeProjectile(&e, pos, vel, range, speed, "stone", "rolling", Animation(0, 4, 8), std::move(label));


    return &e;
}

Entity* EntityFactory::mintProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string texid, std::string label) {
    auto& e(manager->addEntity());

    forgeProjectile(&e, pos, vel, range, speed, std::move(texid), "", Animation(0,0,0), std::move(label));

    return &e;
}

void EntityFactory::forgeProjectile(Entity* e, Vector2D pos, Vector2D vel, int range, int speed, std::string texid, std::string initId, Animation anim, std::string label){
    e->addGroup(Game::groupProjectiles);
    e->addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
    if(anim.isNull()) 
        e->addComponent<SpriteComponent>(texid);
    else
        e->addComponent<SpriteComponent>(texid, initId, anim);
    e->addComponent<ProjectileComponent>(range, speed, vel);
    e->addComponent<CircleColliderComponent>(label, 16, 16, 16);
    e->addComponent<LabelComponent>(0, -20, label, "entity-arial", white);
}