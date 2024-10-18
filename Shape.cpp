#include "Shape.h"

Shape::Shape(int x, std::array<Coordinate, 3> &shape, uint8_t rotation)
    : center {x, top_boundary - block_size}, rotations {rotation}, default_coors {shape}, curr_coors {}, color {color_of_blocks.at(shape)} {
    curr_coors = default_coors;
}

Shape &Shape::operator=(const Shape &shape) {
    this->center = shape.center;
    this->curr_coors = shape.curr_coors;
    this->rotations = shape.rotations;
    this->default_coors = shape.default_coors;
    this->color = shape.color;

    return *this;
}

void Shape::move_down() {
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
    uint8_t previous_roation {rotations};
    rotations = (rotations + 1) % possible_rotations;
    SDL_Log("Rotations: %d", rotations);
    calc_coors();
    bool out = is_out_of_bounds();
    SDL_Log("Out of bounds: %s", out ? "true" : "false");
    if (out)
        rotations = previous_roation;
    calc_coors();
}

std::array<Coordinate, 4> Shape::get_raw_coordinates(int offset_x, int offset_y) const {
    std::array<Coordinate, 4> coors;
    if (offset_x == 0)
        offset_x = center.first;
    if (offset_y == 0)
        offset_y = center.second;
    int curr_coor {0};
    for (const auto &[x, y]: curr_coors) {
        coors[curr_coor] = Coordinate {x * block_size + offset_x, y * block_size + offset_y};
        curr_coor++;
    }
    coors[coors.size() - 1] = Coordinate {offset_x, offset_y};
    return coors;
}

void Shape::draw(SDL_Renderer *renderer, int offset_x, int offset_y) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
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

bool Shape::is_out_of_bounds() const {
    for (auto [x, y]: get_raw_coordinates())
        if (x + block_size > right_boundary || x < left_boundary || y + block_size > bottom_boundary)
            return true;
    return false;
}

std::optional<std::array<Coordinate, 4>> Shape::landed_at_bottom(const std::array<std::array<SDL_Color, 12>, 21> &grid) const {
    auto coors {get_raw_coordinates()};
    for (auto [x, y]: coors) {
        if (y + block_size >= bottom_boundary)
            return {coors};
        int grid_y {-1};
        for (const auto &row: grid) {
            grid_y++;
            int grid_x {-1};
            for (SDL_Color color: row) {
                grid_x++;
                if (color.r == 0 && color.g == 0 && color.b == 0 && color.a == 0)
                    continue;
                int actual_x {grid_x * block_size + left_boundary};
                int actual_y {grid_y * block_size + left_boundary};
                if (actual_x != x)
                    continue;
                if (y + 20 == actual_y)
                    return {coors};
            }
        }
    }
    return {};
}

void Shape::move_right() {
    center.first += speed;
}
