#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "Graphic.h"

class TextObj
{
public:
    TextObj();
    ~TextObj() {}

    bool Load_Text(TTF_Font *font, SDL_Renderer* renderer, const char*str);
    void Free();

    void RenderText(SDL_Renderer *renderer, int x, int y, SDL_Rect*clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    SDL_Texture* texture;
    SDL_Color text_color;
    int width, height;

};

#endif // TEXT_H_INCLUDED
