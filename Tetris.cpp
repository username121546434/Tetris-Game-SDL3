#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_iostream.h>
#include "Next_block.h"
#include "Score.h"
#include <map>
#include "TextRenderer.h"
#include "draw_grid.h"
#include <vector>

static int score {0};

struct AppData {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int score;
    Shape curr_shape;
    Shape next_shape;
    //std::map<const std::array<Coordinate, 3>&, short> cached_rotation;
    std::array<std::array<SDL_Color, 12>, 21> grid;
    TextRenderer text;
    TextRenderer score_text;
    uint64_t last_tick;
    bool game_over;
};

void check_if_block_landed(AppData *ad) {
    auto landed {ad->curr_shape.landed_at_bottom(ad->grid)};
    if (landed) {
        auto game_over {ad->next_shape.landed_at_bottom(ad->grid)};
        if (game_over) {
            ad->game_over = true;
            return;
        }
        for (auto [x, y]: *landed) {
            auto [grid_x, grid_y] = to_grid_coordinates(x, y);
            if (grid_x < 0 || grid_y < 0)
                continue;
            ad->grid.at(grid_y).at(grid_x) = ad->curr_shape.color;
        }
        ad->curr_shape = ad->next_shape;
        ad->next_shape = Shape {130, get_next_block()};
    }
}

std::vector<int> check_if_row_is_made(const AppData &ad) {
    int y {0};
    std::vector<int> rows;
    rows.reserve(ad.grid.size());
    for (const auto &row: ad.grid) {
        int x {-1};
        bool full_row {true};
        for (SDL_Color color: row) {
            x++;
            if (color.r == 0 && color.g == 0 && color.b == 0) {
                full_row = false;
                break;
            }
        }
        if (full_row)
            rows.push_back(y);
        y++;
    }

    return rows;
}

void remove_rows(AppData &ad, const std::vector<int> &rows) {
    for (auto row_to_be_removed: rows) {
        for (int r {row_to_be_removed}; r >= 0; r--) {
            int x {0};
            for (auto &color: ad.grid.at(r)) {
                SDL_Color above_color;
                if (r != 0)
                    above_color = ad.grid.at(r - 1).at(x);
                else
                    above_color = {0, 0, 0, 0};
                color.r = above_color.r;
                color.g = above_color.g;
                color.b = above_color.b;
                color.a = above_color.a;
                x++;
            }
        }
    }
    ad.score += rows.size() * 10;
}

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
    //ad->cached_rotation = std::map<const std::array<Coordinate, 3>&, short> {};
    ad->score = 0;
    ad->curr_shape = Shape {130, get_next_block()};
    ad->next_shape = Shape {130, get_next_block()};
    ad->grid = std::array<std::array<SDL_Color, 12>, 21> {};
    ad->window = window;
    ad->renderer = renderer;
    ad->text = TextRenderer {std::string {font_file}, font_size};
    ad->score_text = TextRenderer {std::string {font_file}, score_font_size};
    ad->last_tick = SDL_GetTicks();
    ad->game_over = false;

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
            ad->curr_shape.move_right(ad->grid);
        } else if (event->key.key == SDLK_LEFT) {
            ad->curr_shape.move_left(ad->grid);
        } else if (event->key.key == SDLK_DOWN) {
            if (!ad->curr_shape.intersects_with_grid(ad->grid)) {
                ad->curr_shape.move_down();
                ad->score++;
                check_if_block_landed(ad);
                auto rows {check_if_row_is_made(*ad)};
                remove_rows(*ad, rows);
            }
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
    draw_next_block_widget(renderer, ad->next_shape, ad->text);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    draw_score_widget(renderer, ad->score, ad->text, ad->score_text);
    draw_grid(renderer, ad->grid);
    ad->curr_shape.draw(renderer);
    
    if (SDL_GetTicks() - ad->last_tick >= 500) {
        ad->curr_shape.move_down();
        ad->last_tick = SDL_GetTicks();
        check_if_block_landed(ad);
        remove_rows(*ad, check_if_row_is_made(*ad));
    }

    SDL_RenderPresent(renderer);

    if (ad->game_over)
        return SDL_APP_SUCCESS;

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_free(appstate);
    TTF_Quit();
    /* SDL will clean up the window/renderer for us. */
}