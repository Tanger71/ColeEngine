#pragma once

/**
 * @brief Struct to handle Circles
 *
 * @author sawyercoletang
 *
 */
struct Circle {
    int x;
    int y;
    int r;

    Circle() = default;

    /**
     *
     * @param x x position
     * @param y y position
     * @param r radius
     */
    Circle(int x, int y, int r) : x(x), y(y), r(r){}

    /**
     * @brief static function to draw circle
     *
     * @note https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
     *
     * @param c Circle struct pointer
     */
    static void drawCircle(Circle* c){
        const int diameter = (c->r * 2);

        int x = (c->r - 1);
        int y = 0;
        int tx = 1;
        int ty = 1;
        int error = (tx - diameter);

        while (x >= y)
        {
            //  Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(Game::renderer, c->x + x, c->y - y);
            SDL_RenderDrawPoint(Game::renderer, c->x + x, c->y + y);
            SDL_RenderDrawPoint(Game::renderer, c->x - x, c->y - y);
            SDL_RenderDrawPoint(Game::renderer, c->x - x, c->y + y);
            SDL_RenderDrawPoint(Game::renderer, c->x + y, c->y - x);
            SDL_RenderDrawPoint(Game::renderer, c->x + y, c->y + x);
            SDL_RenderDrawPoint(Game::renderer, c->x - y, c->y - x);
            SDL_RenderDrawPoint(Game::renderer, c->x - y, c->y + x);

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
    }
};