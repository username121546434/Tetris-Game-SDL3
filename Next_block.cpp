#include "Next_block.h"

std::array<std::pair<int, int>, 3> get_next_block() {
	return all_blocks[SDL_rand(all_blocks.size())];
}

void draw_next_block_widget(SDL_Renderer *renderer) {
    SDL_RenderLine(renderer, 370, 100, 470, 100);
    SDL_RenderLine(renderer, 370, 100, 370, 200);
    SDL_RenderLine(renderer, 370, 200, 470, 200);
    SDL_RenderLine(renderer, 470, 100, 470, 200);
}
