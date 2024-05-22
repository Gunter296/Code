#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED

#include "Penguin.h"
#include "Timer.h"
#include "Graphic.h"

#define throw_speed 4
#define max_throw_speed 30
#define negative_max_speed -30

/* -------------------------------------------------------------------------------------------

Obstacle address:  +)  "E:\\SDLfirst\\myGame\\photo\\Obstacle\\meteorite.png"
                    +)  "E:\\SDLfirst\\myGame\\photo\\Obstacle\\Snowball\\Snowball_right.png"

---------------------------------------------------------------------------------------------*/

class Obstacle : public Image
{
public:
    Obstacle();
    ~Obstacle() {}
    bool load_obstacle(const char* filename, SDL_Renderer *renderer);
    bool Move();
    void Random_throw(Map &map_data);
    void show(SDL_Renderer* renderer);

    void set_default();

    SDL_Rect getRect();




private:
    float dx, dy, x, y, x_move;
    int width_frame, height_frame;
    SDL_Rect frame_clips[FRAME];
    int frame, status;
};

#endif // OBSTACLE_H_INCLUDED
