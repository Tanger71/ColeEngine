//
// Created by Sawyer Tang on 11/14/22.
//

#pragma once
#include "Components.h"

class PositionComponent : public Component{
private:
    int xpos = 0;
    int ypos = 0;
public:
    PositionComponent(){
        xpos = 0;
        ypos = 0;
    }

    PositionComponent(int x, int y){
        xpos = x;
        ypos = y;
    }

    void update() override {
        xpos++;
        ypos++;
    }

    int x() { return xpos; }
    void x(int x) { xpos = x; }
    int y() { return ypos; }
    void y(int y) { ypos = y; }
    void setPos(int x, int y){xpos = x; ypos = y;}

//    void init() override {
//        xpos = 0;
//        ypos = 0;
//    }

};