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
    Coordinate center;
    uint8_t rotations; // ranges from 0 to 3
    std::array<Coordinate, 3> default_coors;
    std::array<Coordinate, 3> curr_coors;
public:
    SDL_Color color;

    Shape(int x, std::array<Coordinate, 3> &shape, uint8_t rotation = 0);
    Shape &operator=(const Shape &);
    void calc_coors();
    void rotate();
    std::array<Coordinate, 4> get_raw_coordinates(int offset_x = 0, int offset_y = 0) const;
    std::array<Coordinate, 4> get_grid_coordinates(int offset_x = 0, int offset_y = 0) const;
    void draw(SDL_Renderer *renderer, int offset_x = 0, int offset_y = 0) const;
    void move_down();
    void move_right(const std::array<std::array<SDL_Color, 12>, 21> &grid);
    void move_left(const std::array<std::array<SDL_Color, 12>, 21> &grid);
    bool is_out_of_bounds() const;
    bool intersects_with_grid(const std::array<std::array<SDL_Color, 12>, 21> &grid) const;
    std::optional<std::array<Coordinate, 4>> landed_at_bottom(const std::array<std::array<SDL_Color, 12>, 21> &grid) const;
};

Coordinate to_grid_coordinates(int x, int y);

#endif