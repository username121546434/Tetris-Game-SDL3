#pragma once
#include <array>

constexpr int block_size {20};
constexpr int speed {block_size};
constexpr int window_height {480};
constexpr int window_width {480};

constexpr std::array<std::pair<int, int>, 3> block_L {
    std::pair {0, -1}, /*  center   */
    std::pair {0,  1}, std::pair {1, 1}
};

constexpr std::array<std::pair<int, int>, 3> block_reversed_L {
     /*  center   */   std::pair {0, -1},
    std::pair {-1, 1}, std::pair {0, 1}
};

constexpr std::array<std::pair<int, int>, 3> block_square {
     /*  center   */  std::pair {1, 0},
    std::pair {0, 1}, std::pair {1, 1}
};

constexpr std::array<std::pair<int, int>, 3> block_podium {
                      std::pair {0, -1},
    std::pair {-1, 0}, /*  center   */  std::pair {1, 0}
};

constexpr std::array<std::pair<int, int>, 3> block_Z {
    std::pair {-1, -1}, std::pair {0, -1},
                        /*  center   */   std::pair {1, 0}
};

constexpr std::array<std::pair<int, int>, 3> block_reversed_Z {
                                std::pair {0, -1}, std::pair {1, -1},
    std::pair {-1, 0} /*  center   */
};

constexpr std::array<std::pair<int, int>, 3> block_line {
    std::pair {0, -1},
    /*    center    */
    std::pair {0, 1},
    std::pair {0, 2}
};

constexpr std::array<std::array<std::pair<int, int>, 3>, 7> all_blocks {
    block_L,
    block_reversed_L,
    block_line,
    block_podium,
    block_Z,
    block_reversed_Z,
    block_square
};

