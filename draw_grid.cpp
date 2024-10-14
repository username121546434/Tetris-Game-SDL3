#include "draw_grid.h"
#include <sstream>

void draw_grid(SDL_Renderer *renderer, const std::array<std::array<SDL_Color, 12>, 21> &grid) {
    SDL_RenderLine(renderer, left_boundary, top_boundary, left_boundary, bottom_boundary);
    SDL_RenderLine(renderer, right_boundary, top_boundary, right_boundary, bottom_boundary);
    SDL_RenderLine(renderer, left_boundary, bottom_boundary, right_boundary, bottom_boundary);
    
    int y {0};
    for (const auto &row: grid) {
        int x {0};
        for (SDL_Color color: row) {
            SDL_FRect rect {
                x * block_size + left_boundary, y * block_size + top_boundary,
                block_size, block_size
            };
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 1);
            SDL_RenderFillRect(renderer, &rect);
            x++;
        }
        y++;
    }
}
