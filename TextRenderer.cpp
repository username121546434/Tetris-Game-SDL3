#include "TextRenderer.h"

TextRenderer::TextRenderer(const std::string &fontFile, float fontSize)
    : fontFile {fontFile}, fontSize {fontSize} {
    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (!font)
        SDL_Log("Error opening font %s: %s", fontFile.c_str(), SDL_GetError());
}

TextRenderer::~TextRenderer() {
    if (font)
        TTF_CloseFont(font);
}

TextRenderer::TextRenderer(TextRenderer &&rhs) noexcept
    : fontFile {rhs.fontFile}, font {rhs.font}, fontSize {rhs.fontSize} {

    rhs.font = nullptr;
}

// copy assignment
TextRenderer &TextRenderer::operator=(const TextRenderer &rhs) {
    if (this == &rhs)
        return *this;
    TTF_CloseFont(font);
    this->font = TTF_OpenFont(rhs.fontFile.c_str(), rhs.fontSize);
    this->fontFile = rhs.fontFile;
    this->fontSize = rhs.fontSize;

    return *this;
}

TextRenderer &TextRenderer::operator=(TextRenderer &&rhs) {
    if (this == &rhs)
        return *this;
    TTF_CloseFont(font);
    font = rhs.font;
    rhs.font = nullptr;
    this->fontFile = std::string {rhs.fontFile};
    this->fontSize = rhs.fontSize;

    return *this;
}


void TextRenderer::renderText(SDL_Renderer *renderer, const std::string &text, int x, int y) const {
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), 0, color);
    if (!surface) SDL_LogError(SDL_LogCategory::SDL_LOG_CATEGORY_ERROR, "Failed to create surface: %s", SDL_GetError());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) SDL_LogError(SDL_LogCategory::SDL_LOG_CATEGORY_ERROR, "Failed to create texture: %s", SDL_GetError());
    if (!surface || !texture)
        return;

    SDL_Rect dstRect {x, y, surface->w, surface->h};
    SDL_FRect d;
    SDL_RectToFRect(&dstRect, &d);
    SDL_RenderTexture(renderer, texture, NULL, &d);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

