#ifndef SHAPE_H
#define SHAPE_H

#pragma once

#include <array>
#include "constants.h"
#include <SDL3/SDL.h>

class Shape {

private:
    std::pair<int, int> center;
    short rotations; // ranges from 0 to 3
    std::array<std::pair<int, int>, 3> const *default_coors;
    std::array<std::pair<int, int>, 3> curr_coors;
public:
    Shape(int x, std::array<std::pair<int, int>, 3> &shape, short rotation = 0);
    Shape &operator=(const Shape &);
    void calc_coors();
    void update_center();
    void rotate();
    void draw(SDL_Renderer *renderer, int offset_x = 0, int offset_y = 0) const;
};

#endif