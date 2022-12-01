#include <cmath>
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

//bool Collision::CircleRectangle(const Circle& cir, const SDL_Rect& rect){
//    int circleDistance_x = abs(cir.x - rect.x);
//    int circleDistance_y = abs(cir.y - rect.y);
//
//    if (circleDistance_x > (rect.w/2 + cir.r)) { return false; }
//    if (circleDistance_y > (rect.h/2 + cir.r)) { return false; }
//
//    if (circleDistance_x <= (rect.w/2)) { return true; }
//    if (circleDistance_y <= (rect.h/2)) { return true; }
//
//    int cornerDistance_sq = (circleDistance_x - rect.w/2)^2 + (circleDistance_y - rect.h/2)^2;
//
//    return (cornerDistance_sq <= (cir.r^2));
//}

bool Collision::CircleRectangle(const Circle& cir, const SDL_Rect& rect){
    int circleDistance_x = abs(cir.x - (rect.x + rect.w/2));
    int circleDistance_y = abs(cir.y - (rect.y + rect.h/2));

    if (circleDistance_x > (rect.w/2 + cir.r)) { return false; }
    if (circleDistance_y > (rect.h/2 + cir.r)) { return false; }

    if (circleDistance_x <= (rect.w/2)) { return true; }
    if (circleDistance_y <= (rect.h/2)) { return true; }

    int cornerDistance_sq = std::pow(circleDistance_x - rect.w/2, 2) + std::pow(circleDistance_y - rect.h/2, 2);

    return (cornerDistance_sq <= std::pow(cir.r, 2));
}

bool Collision::AABB(const RectangleColliderComponent& colA, const RectangleColliderComponent& colB) {
    return AABB(colA.collider, colB.collider);
}

bool Collision::CircleRectangle(const CircleColliderComponent& cir, const RectangleColliderComponent& rect){
    return CircleRectangle(cir.collider, rect.collider);
}

bool Collision::CircleCircle(const Circle& cirA, const Circle& cirB){
    return 0;
}
