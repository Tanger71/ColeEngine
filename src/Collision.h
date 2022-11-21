#pragma once
#include "SDL.h"

class ColliderComponent;

/**
 * @brief A library of collision algs.
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
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);

};
