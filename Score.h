#pragma once
#include <SDL3/SDL.h>
#include "TextRenderer.h"

void draw_score_widget(SDL_Renderer *renderer, int score, const TextRenderer &text, const TextRenderer &score_text);
