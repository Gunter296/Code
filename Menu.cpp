#include "Menu.h"

void Menu::build_menu(SDL_Renderer *renderer)
{
    create_menu_image(renderer);
    creat_button(renderer);
}

void Menu::creat_button(SDL_Renderer *renderer)
{
    button_play.loadImage("photo\\PLAY.png", renderer);
    button_play.setDest(449, 192);
    rect.x = button_play.dest.x;
    rect.y = button_play.dest.y;
    rect.w = button_play.dest.w;
    rect.h = button_play.dest.h;
    button_play.Draw(renderer);
}

void Menu::create_menu_image(SDL_Renderer* renderer)
{
    Image menu;
    menu.loadImage("photo\\menu.jpg", renderer);
    menu.createImage(renderer);
}

bool Menu::check_mouse_button(SDL_Renderer *renderer, int x, int y)
{

    if( x>= rect.x && x<=rect.x+ rect.w && y>= rect.y && y<= rect.y + rect.h)
    {
        button_play.Free();
        Image play_button;
        play_button.loadImage("photo\\PLAY_press.png", renderer);
        play_button.setDest( 449, 192);
        play_button.Draw(renderer);
        return true;
    }
}

void Menu::Score_board(SDL_Renderer* renderer)
{
    Image score;
    score.loadImage("photo\\Score.png", renderer);
    score.setDest(448, 128);
    rect.x = score.dest.x;
    rect.y = score.dest.y;
    rect.w = score.dest.w;
    rect.h = score.dest.h;
    score.Draw(renderer);
}
