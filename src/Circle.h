#pragma once

struct Circle {
    int xpos;
    int ypos;
    int radius;

    Circle() = default;

    Circle(int x, int y, int r) : xpos(x), ypos(y), radius(r){}
};