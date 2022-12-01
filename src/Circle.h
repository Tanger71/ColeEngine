#pragma once

struct Circle {
    int x;
    int y;
    int r;

    Circle() = default;

    Circle(int x, int y, int r) : x(x), y(y), r(r){}

    /**
     *
     * @note https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
     *
     * @param c
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