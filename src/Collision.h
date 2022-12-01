#pragma once
#include "SDL.h"
#include "ECS/Components.h"
#include "Circle.h"

//class ColliderComponent; //removed this fixed bug

/**
 * @brief A library of collision algs.
 *
 * @note currently supports axis-aligned rectangles
 *
 * @author sawyercoletang
 *
 */
class Collision {
public:

    /**
     * @brief axis-aligned bounding box for SDL_Rect
     *
     * @note might remove cause of the ColliderComponent overload
     *
     * @param recA
     * @param recB
     * @return true if A and B are overlapping
     */
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);

    /**
     * @brief axis-aligned bounding box for ColliderComponents
     *
     * @param colA
     * @param colB
     * @return true if A and B are overlapping
     */
	static bool AABB(const RectangleColliderComponent& colA, const RectangleColliderComponent& colB);

    static bool CircleRectangle(const Circle& cir, const SDL_Rect& rect);

    static bool CircleRectangle(const CircleColliderComponent& cir, const RectangleColliderComponent& rect);


    static bool CircleCircle(const Circle& cirA, const Circle& cirB);

};
