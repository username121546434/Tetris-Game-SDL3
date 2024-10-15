#ifndef SHAPE_H
#define SHAPE_H

#pragma once

#include <array>
#include "constants.h"
#include <SDL3/SDL.h>
#include <array>
#include <optional>

class Shape {

private:
    std::pair<int, int> center;
    uint8_t rotations; // ranges from 0 to 3
    std::array<std::pair<int, int>, 3> default_coors;
    std::array<std::pair<int, int>, 3> curr_coors;
public:
    SDL_Color color;

    Shape(int x, std::array<std::pair<int, int>, 3> &shape, uint8_t rotation = 0);
    Shape &operator=(const Shape &);
    void calc_coors();
    void update_center();
    void rotate();
    std::array<std::pair<int, int>, 4> get_raw_coordinates(int offset_x = 0, int offset_y = 0) const;
    void draw(SDL_Renderer *renderer, int offset_x = 0, int offset_y = 0) const;
    void move_right();
    void move_left();
    bool is_out_of_bounds() const;
    std::optional<std::array<std::pair<int, int>, 4>> landed_at_bottom(const std::array<std::array<SDL_Color, 12>, 21> &grid) const;
};

#endif