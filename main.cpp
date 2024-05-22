#include "Graphic.h"
#include "LoadImage.h"
#include "gameMap.h"
#include "Penguin.h"
#include "Timer.h"
#include "Obstacle.h"
#include "Menu.h"
#include "Text.h"



int main(int argc, char* argv[])
{
    graphic g;
    g.Init();

    Mix_Music *gMusic = loadMusic("sound\\Hyper Potions.mp3");
    play(gMusic, -1);

    TTF_Font *font;
    font = TTF_OpenFont("upheavtt.ttf", 60);

    SDL_Event event;


    Time imp_time;


    Image background;

    GameMap game_map;
    game_map.LoadMap("map.txt");

    Character player;


    Obstacle Snowball;


    Menu menu;

    int x,y, time = 0;
    bool quit = false;
    bool stop = false;
    bool isMenu = true;
    while(!quit)
    {
    SDL_GetMouseState(&x, &y);
    imp_time.start();

    if(isMenu == true)
    {
        imp_time.pause();

        SDL_RenderClear(g.renderer);
        menu.build_menu(g.renderer);
        menu.check_mouse_button(g.renderer, x, y);
        while( SDL_PollEvent(&event) != 0 )
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }

            if(event.type==SDL_MOUSEBUTTONDOWN)
                {
                    SDL_GetMouseState(&x, &y);
                    if( !menu.check_mouse_button(g.renderer, x, y) )
                    {
                        isMenu = true;
                    }
                    else isMenu = false;
                }
        }
        SDL_RenderPresent(g.renderer);
    }
    else
    {
        imp_time.unpause();

        if(stop == true)
            {
                Snowball.Free();
                menu.Score_board(g.renderer);
                TextObj tes_text;
                tes_text.setColor(61, 207, 212);
                string s = "SCORE:";
                stringstream ss;
                int score = (int)time/30;
                if(score < 10)
                {
                    ss << s << 0 << score;
                }
                else
                {
                    ss << s << score;
                }
                string text = ss.str();

                tes_text.Load_Text(font, g.renderer, text.c_str());
                tes_text.RenderText(g.renderer, 500, 280);
                    SDL_PollEvent(&event);
                    switch (event.type)
                    {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        isMenu = true;
                        player.set_default();
                        Snowball.set_default();
                        time = 0;
                        stop = false;
                        break;
                    }
                    SDL_RenderPresent(g.renderer);
            }
        else
        {
            if(!background.loadImage("photo\\BG.jpg", g.renderer) )
            {
                logErrorAndExit("Can't create background because", SDL_GetError());

            }


            game_map.LoadTile(g.renderer);

            player.load_object_image("photo\\penguin\\penguin_right_60_64.png", g.renderer);
            player.clips();



            while( SDL_PollEvent(&event) != 0 )
            {
                if(event.type == SDL_QUIT)
                {
                    quit = true;
                }
                player.InputAction(g.renderer, event);
            }

            SDL_RenderClear(g.renderer);

            background.createImage(g.renderer);

            game_map.DrawMap(g. renderer);
            Map data = game_map.getMap();


            if(player.Move(data)==false) stop = true;
            player.show(g.renderer);

            if( ( (int) time/30 ) > 5)
            {
                if(!Snowball.Move() )
                {
                    Snowball.Random_throw(data);
                }

                Snowball.show(g.renderer);
            }


            SDL_Rect player_rect = player.getRect();
            SDL_Rect obstacle_rect = Snowball.getRect();
            if ( CheckCollision(obstacle_rect, player_rect) )
            {
                player.died = true;
                stop = true;
            }


            SDL_RenderPresent(g.renderer);
            int real_time = imp_time.get_tick();
            int frame_time  = 1000/FPS;
            if(real_time < frame_time)
            {
                int delay_time = frame_time - real_time;
                if(delay_time>=0)
                {
                    SDL_Delay(delay_time);
                }
            }
            time++;
        }
    }
}
    if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    game_map.FreeMap();
    player.Free();
    background.Free();
	g.release();
	return 0;
}
