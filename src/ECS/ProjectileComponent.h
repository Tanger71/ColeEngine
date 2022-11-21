#pragma once
#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"

/**
 * @brief Component for projectiles.
 *
 * @author sawyercoletang
 *
 */
class ProjectileComponent : public Component {
public:

    /**
     *
     * @param rng projectile range before destroy
     * @param sp projectile speed
     * @param vel projectile velocity
     */
	ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel){}
	~ProjectileComponent() {}

    /**
     * @brief initialize the component: link to TransformComponent.
     */
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

    /**
     * @brief update the component.
     */
	void update() override {
		distance += speed;

		if (distance > range) { //POPE
			std::cout << "out of range" << std::endl;
			entity->destroy();
		} else if (transform->position.x > Game::camera.x + Game::camera.w || // todo: only good for if proj is faster than camera
			transform->position.x < Game::camera.x ||
			transform->position.y > Game::camera.y + Game::camera.h ||
			transform->position.y < Game::camera.y)
		{
			std::cout << "out of bounds" << std::endl;
			entity->destroy();
		}
	}

private:
	TransformComponent* transform;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;

};