#include "draw_grid.h"
#include <sstream>

void draw_grid(SDL_Renderer *renderer, const std::array<std::array<SDL_Color, 7>, 14> &grid) {
    SDL_RenderLine(renderer, left_boundary, top_boundary, left_boundary, bottom_boundary);
    SDL_RenderLine(renderer, right_boundary, top_boundary, right_boundary, bottom_boundary);
    SDL_RenderLine(renderer, left_boundary, bottom_boundary, right_boundary, bottom_boundary);

    //for (const auto &row: grid) {
    //    std::stringstream s {};
    //    s << "{";
    //    for (auto color: row) {
    //        s << "(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
    //    }
    //    s << "}" << std::endl;
    //    SDL_Log(s.str().c_str());
    //}
}
