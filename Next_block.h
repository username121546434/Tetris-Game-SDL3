#pragma once

#include "constants.h"
#include <SDL3/SDL.h>
#include <map>
#include "Shape.h"

std::array<std::pair<int, int>, 3> get_next_block();

void draw_next_block_widget(SDL_Renderer *renderer, const Shape &shape);
