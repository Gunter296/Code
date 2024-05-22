#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Graphic.h"
#include "LoadImage.h"

class Menu : public Image
{
public:
    void build_menu(SDL_Renderer* renderer);

    bool check_mouse_button(SDL_Renderer *renderer, int x, int y);

    void creat_button(SDL_Renderer *renderer);

    void create_menu_image(SDL_Renderer *renderer);

    void Score_board(SDL_Renderer *renderer);

    Image button_play;

    SDL_Rect rect;

};

#endif // MENU_H_INCLUDED
