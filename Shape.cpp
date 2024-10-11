#include "Shape.h"

Shape::Shape(int x, std::array<std::pair<int, int>, 3> &shape, short rotation)
    : center {x, 0}, rotations {rotation}, default_coors {shape}, curr_coors {} {
    curr_coors = default_coors;
}

void Shape::update_center() {
    center.second += speed;
}

void Shape::rotate() {
    rotations = ++rotations % 4;
    calc_coors();
}

void Shape::draw(SDL_Renderer *renderer, int offset_x, int offset_y) {
    std::array<SDL_FRect, 4> blocks {};
    int curr_block {0};
    for (const auto &[x, y]: curr_coors) {
        blocks[curr_block] = SDL_FRect {
            static_cast<float>(x * block_size) + offset_x, static_cast<float>(y * block_size) + offset_y,
            block_size, block_size
        };
        curr_block++;
    }

    SDL_RenderRects(renderer, blocks.data(), blocks.size());
}

void Shape::calc_coors() {
    std::array<std::pair<int, int>, 3> curr_coors {default_coors};
    int tmp {};
    for (int i {0}; i < rotations; i++)
        for (auto &[x, y]: curr_coors) {
            tmp = x;
            x = -y;
            y = tmp;            
        }
}