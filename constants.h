#pragma once
#include <array>
#include <string>
#include <map>
#include <SDL3/SDL.h>

typedef std::pair<int, int> Coordinate;

constexpr int block_size {20};
constexpr int speed {block_size};
constexpr int window_height {480};
constexpr int window_width {480};
constexpr int block_rows {21};
constexpr int block_cols {12};

constexpr int left_boundary {30};
constexpr int right_boundary {270};
constexpr int bottom_boundary {450};
constexpr int top_boundary {30};

constexpr std::string_view font_file = "game_over.ttf";
constexpr int font_size {60};
constexpr int score_font_size {100};

constexpr std::array<Coordinate, 3> block_L {
    std::pair {0, -1}, /*  center   */
    std::pair {0,  1}, std::pair {1, 1}
};

constexpr std::array<Coordinate, 3> block_reversed_L {
     /*  center   */   std::pair {0, -1},
    std::pair {-1, 1}, std::pair {0, 1}
};

constexpr std::array<Coordinate, 3> block_square {
     /*  center   */  std::pair {1, 0},
    std::pair {0, 1}, std::pair {1, 1}
};

constexpr std::array<Coordinate, 3> block_podium {
                      std::pair {0, -1},
    std::pair {-1, 0}, /*  center   */  std::pair {1, 0}
};

constexpr std::array<Coordinate, 3> block_Z {
    std::pair {-1, -1}, std::pair {0, -1},
                        /*  center   */   std::pair {1, 0}
};

constexpr std::array<Coordinate, 3> block_reversed_Z {
                                std::pair {0, -1}, std::pair {1, -1},
    std::pair {-1, 0} /*  center   */
};

constexpr std::array<Coordinate, 3> block_line {
    std::pair {0, -1},
    /*    center    */
    std::pair {0, 1},
    std::pair {0, 2}
};

constexpr std::array<std::array<Coordinate, 3>, 7> all_blocks {
    block_L,
    block_reversed_L,
    block_line,
    block_podium,
    block_Z,
    block_reversed_Z,
    block_square
};

const std::map<std::array<Coordinate, 3>, SDL_Color> color_of_blocks {
    {block_L, {173, 235, 150, 1}},
    {block_reversed_L, {150, 235, 219, 1}},
    {block_line, {118, 29, 150, 1}},
    {block_podium, {237, 228, 62, 1}},
    {block_Z, {237, 123, 62, 1}},
    {block_reversed_Z, {237, 62, 62, 1}},
    {block_square, {84, 90, 247, 1}},
};

