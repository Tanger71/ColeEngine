#pragma once
#include "Components.h"

class FSMComponent : public Component {

protected:
    enum State : std::size_t;
    State curState;
public:
    FSMComponent(){}
    ~FSMComponent(){}

    void init() override{}

    void update() override{}

};
