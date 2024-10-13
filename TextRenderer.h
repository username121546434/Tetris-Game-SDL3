#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class TextRenderer {
    std::string fontFile;
    float fontSize;
    TTF_Font *font;
public:
    TextRenderer(const std::string &fontFile, float fontSize);
    ~TextRenderer();
    TextRenderer(TextRenderer &&rhs) noexcept;
    TextRenderer &operator=(const TextRenderer &rhs);
    TextRenderer &operator=(TextRenderer &&rhs);
    void renderText(SDL_Renderer *renderer, const std::string &text, int x, int y) const;
};

