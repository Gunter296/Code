#ifndef COMMONFUCT_H_INCLUDED
#define COMMONFUCT_H_INCLUDED

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mouse.h>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <SDL_mixer.h>


using namespace std;

/***********************************************************************/
const int SCREEN_WIDTH = 1280; //1280
const int SCREEN_HEIGHT = 640; // 640
// Background address : "photo\\map\\BG.png"

/**********************************************************************/



//---------------------------------------------------------------------------------
void logErrorAndExit(const char* msg, const char* error);


Mix_Music *loadMusic(const char* path);
void play(Mix_Music *gMusic, int loop);

struct graphic
{
    SDL_Renderer *renderer;
    SDL_Window *window;

    void Init();
    void release();

};

void waitUntilKeyPressed();

bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
//---------------------------------------------------------------------------------

#define MAX_MAP_X  20
#define MAX_MAP_Y  10
#define TILE_SIZE  64
#define Blank 0

struct Map
{
    int max_x, max_y;
    int tile[MAX_MAP_Y][MAX_MAP_X];
    char *filename;
};


struct Input
{
    int left_;
    int right_;
    int jump_;
};
#endif // COMMONFUCT_H_INCLUDED
