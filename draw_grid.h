#pragma once

#include <SDL3/SDL.h>
#include <array>
#include "constants.h"

void draw_grid(SDL_Renderer *renderer, const std::array<std::array<SDL_Color, 7>, 14> &grid);

