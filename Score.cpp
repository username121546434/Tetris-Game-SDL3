#include "Score.h"

void draw_score_widget(SDL_Renderer *renderer, int score, const TextRenderer &text) {
    SDL_RenderLine(renderer, 370, 300, 470, 300);
    SDL_RenderLine(renderer, 370, 300, 370, 400);
    SDL_RenderLine(renderer, 370, 400, 470, 400);
    SDL_RenderLine(renderer, 470, 300, 470, 400);

    text.renderText(renderer, "Score", 385, 300);

    SDL_Log("Score: %d", score);
}
