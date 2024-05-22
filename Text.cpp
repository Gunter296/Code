#include "Text.h"

TextObj::TextObj()
{
    texture = NULL;
    text_color.a = 0;
    text_color.b = 255;
    text_color.g = 255;
    text_color.r = 255;
}

bool TextObj::Load_Text(TTF_Font *font, SDL_Renderer* renderer,const char* str)
{
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, str, text_color);
    if(text_surface)
    {
        texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        width = text_surface->w;
        height = text_surface->h;

        SDL_FreeSurface(text_surface);
    }
    return texture != NULL;
}

void TextObj::Free()
{
    if(texture!=NULL)
    {
        SDL_DestroyTexture(texture);
        texture= NULL;
    }
}

void TextObj::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color.b = blue;
    text_color.g = green;
    text_color.r = red;
}

void TextObj::RenderText(SDL_Renderer *renderer, int x, int y, SDL_Rect*clip, double angle, SDL_Point* center , SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, width, height};
    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip );
}
