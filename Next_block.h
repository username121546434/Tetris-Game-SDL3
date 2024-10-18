#pragma once

#include "constants.h"
#include <SDL3/SDL.h>
#include <map>
#include "Shape.h"
#include "TextRenderer.h"

std::array<Coordinate, 3> get_next_block();

void draw_next_block_widget(SDL_Renderer *renderer, const Shape &shape, const TextRenderer &text);
