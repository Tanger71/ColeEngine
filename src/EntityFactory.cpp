#include "EntityFactory.h"
#include "ECS/Components.h"
#include "Game.h"

EntityFactory::EntityFactory(Manager* man) : manager(man) {
    white = {255, 255, 255, 255}; // TODO: lift scope

}

Entity* EntityFactory::mintPlayer(float xpos, float ypos, std::string label){
    auto& e(manager->addEntity()); //TODO: learn this IMP... what is this syntax?

    e.addGroup(Game::groupPlayers);

    e.addComponent<TransformComponent>(xpos, ypos, 32, 32, 2.0f);

    e.addComponent<SpriteComponent>("player", "Idle", Animation(5, 10, 10));
    e.getComponent<SpriteComponent>().addAnimation("Walk", Animation(7, 10, 10));

    e.addComponent<RectangleColliderComponent>("player", 16, 0, 32, 64);

    e.addComponent<PlayerController>();

    e.addComponent<LabelComponent>(0, -20, label, "entity-arial", white);

    return &e;
}

Entity* EntityFactory::mintWorm(float xpos, float ypos, std::string label){
    auto& e(manager->addEntity());
    e.addGroup(Game::groupEnemies);

    e.addComponent<TransformComponent>(xpos, ypos, 32, 32, 2.0f);

    e.addComponent<SpriteComponent>("worm", "Out", Animation(2, 1, 10));
    e.getComponent<SpriteComponent>().addAnimation("Hiding", Animation(2, 8, 5));
    e.getComponent<SpriteComponent>().addAnimation("In", Animation(1, 1, 30));
    e.getComponent<SpriteComponent>().addAnimation("Emerging", Animation(1, 8, 5));

    e.addComponent<RectangleColliderComponent>("worm", 0, 0, 64, 64);
    e.addComponent<CircleColliderComponent>("worm", 32, 32, 200);

    e.addComponent<WormFSM>();

    e.addComponent<LabelComponent>(0, -20, label, "entity-arial", white);

    return &e;
}

Entity* EntityFactory::mintProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string texid) {
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	projectile.addComponent<SpriteComponent>(texid);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<RectangleColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);

    return &projectile;
}