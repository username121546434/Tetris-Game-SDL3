#include "draw_grid.h"
#include <sstream>

void draw_grid(SDL_Renderer *renderer, const std::array<std::array<SDL_Color, 7>, 14> &grid) {
    SDL_RenderLine(renderer, 30, 30, 30, 450);
    SDL_RenderLine(renderer, 270, 30, 270, 450);
    SDL_RenderLine(renderer, 30, 450, 270, 450);

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
