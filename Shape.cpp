#include "Shape.h"

Shape::Shape(int x, std::array<std::pair<int, int>, 3> &shape, short rotation)
    : center {x, 10}, rotations {rotation}, default_coors {shape}, curr_coors {} {
    curr_coors = default_coors;
}

Shape &Shape::operator=(const Shape &shape) {
    this->center = shape.center;
    this->curr_coors = shape.curr_coors;
    this->rotations = shape.rotations;
    this->default_coors = shape.default_coors;

    return *this;
}

void Shape::update_center() {
    center.second += speed;
    SDL_Log("%d", center.second);
}

void Shape::rotate() {
    if (default_coors == block_square)
        return;
    short possible_rotations = 4;
    if (default_coors == block_Z || default_coors == block_reversed_Z ||
        default_coors == block_line)
        possible_rotations = 2;
        
    rotations = (rotations + 1) % possible_rotations;
    SDL_Log("Rotations: %d", rotations);
    calc_coors();
}

std::array<std::pair<int, int>, 4> Shape::get_raw_coordinates(int offset_x, int offset_y) const {
    std::array<std::pair<int, int>, 4> coors;
    if (offset_x == 0)
        offset_x = center.first;
    if (offset_y == 0)
        offset_y = center.second;
    int curr_coor {0};
    for (const auto &[x, y]: curr_coors) {
        coors[curr_coor] = std::pair<int, int> {x * block_size + offset_x, y * block_size + offset_y};
        curr_coor++;
    }
    coors[coors.size() - 1] = std::pair<int, int> {offset_x, offset_y};
    return coors;
}

void Shape::draw(SDL_Renderer *renderer, int offset_x, int offset_y) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    std::array<SDL_FRect, 4> blocks {};
    int curr_block {0};
    for (const auto &[x, y]: get_raw_coordinates(offset_x, offset_y)) {
        blocks[curr_block] = SDL_FRect {
            static_cast<float>(x), static_cast<float>(y),
            block_size, block_size
        };
        curr_block++;
    }

    SDL_RenderFillRects(renderer, blocks.data(), blocks.size());
}
void Shape::calc_coors() {
    curr_coors = default_coors;
    for (int i {0}; i < rotations; i++)
        for (auto &[x, y]: curr_coors) {
            int tmp = x;
            x = -y;
            y = tmp;            
        }
}

void Shape::move_left() {
    center.first -= speed;
}

void Shape::move_right() {
    center.first += speed;
}
