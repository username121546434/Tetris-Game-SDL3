#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_iostream.h>
#include "Next_block.h"
#include "Score.h"
#include <map>
#include "TextRenderer.h"
#include "draw_grid.h"

static int score {0};

struct AppData {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int score;
    Shape curr_shape;
    //std::map<const std::array<std::pair<int, int>, 3>&, short> cached_rotation;
    std::array<std::array<SDL_Color, 12>, 21> grid;
    TextRenderer text;
    uint64_t last_tick;
};


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Tetris", window_width, window_height, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    AppData *ad = static_cast<AppData*>(SDL_calloc(1, sizeof(AppData)));
    // TODO: make cached rotations work
    //ad->cached_rotation = std::map<const std::array<std::pair<int, int>, 3>&, short> {};
    ad->score = 0;
    ad->curr_shape = Shape {130, get_next_block()};
    ad->grid = std::array<std::array<SDL_Color, 12>, 21> {};
    ad->window = window;
    ad->renderer = renderer;
    ad->text = TextRenderer {std::string {font_file}, font_size};
    ad->last_tick = SDL_GetTicks();

    *appstate = ad;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    AppData *ad {static_cast<AppData *>(appstate)};
    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (event->key.key == SDLK_UP) {
            ad->curr_shape.rotate();
        } else if (event->key.key == SDLK_RIGHT) {
            ad->curr_shape.move_right();
        } else if (event->key.key == SDLK_LEFT) {
            ad->curr_shape.move_left();
        }
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    AppData *ad = static_cast<AppData *>(appstate);
    SDL_Renderer *renderer = ad->renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    draw_next_block_widget(renderer, ad->curr_shape, ad->text);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    draw_score_widget(renderer, 0, ad->text);
    draw_grid(renderer, ad->grid);
    ad->curr_shape.draw(renderer);
    
    if (SDL_GetTicks() - ad->last_tick >= 500) {
        ad->curr_shape.update_center();
        ad->last_tick = SDL_GetTicks();
    }

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_free(appstate);
    TTF_Quit();
    /* SDL will clean up the window/renderer for us. */
}