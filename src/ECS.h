//
// Created by Sawyer Tang on 11/13/22.
//

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID mintComponentID(){
    static ComponentID lastID = 0;
    return lastID++;
}
