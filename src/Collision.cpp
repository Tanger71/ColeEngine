#include "Collision.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		) {
		return true;
	}
	return false;
}

bool Collision::AABB(const RectangleColliderComponent& colA, const RectangleColliderComponent& colB) {
	if (AABB(colA.collider, colB.collider)) {
		return true;
	}
	else {
		return false;
	}
}

bool Collision::CircleRectangle(const Circle& cir, const SDL_Rect& rect){
    return 0;
}

bool Collision::CircleCircle(const Circle& cirA, const Circle& cirB){
    return 0;
}
