#include "Next_block.h"

std::array<Coordinate, 3> get_next_block() {
	return all_blocks[SDL_rand(all_blocks.size())];
}

void draw_next_block_widget(SDL_Renderer *renderer, const Shape &shape, const TextRenderer &text) {
    SDL_RenderLine(renderer, 370, 50, 470, 50);
    SDL_RenderLine(renderer, 370, 50, 370, 200);
    SDL_RenderLine(renderer, 370, 200, 470, 200);
    SDL_RenderLine(renderer, 470, 50, 470, 200);

    text.renderText(renderer, std::string {"Next"}, 390, 50);

    shape.draw(renderer, 410, 125);
}
