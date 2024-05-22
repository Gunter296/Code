#ifndef PENGUIN_H_INCLUDED
#define PENGUIN_H_INCLUDED

#include "Graphic.h"
#include "LoadImage.h"

#define FRAME 13
#define gravity 2
#define max_fall 15
#define player_speed 5
#define jump_val 20

/* -------------------------------------------------------------------------------

character address:  +)  "E:\\SDLfirst\\myGame\\photo\\penguin\\penguin_right.png"
                    +)  "E:\\SDLfirst\\myGame\\photo\\penguin\\penguin_left.png"

-------------------------------------------------------------------------------- */

class Character : public Image
{
public:
    Character();
    ~Character(){}
    float dx, dy, x_pos, y_pos;

    enum WALKTYPE
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
    };

    bool load_object_image(const char* filename, SDL_Renderer *renderer);
    void show(SDL_Renderer *renderer);
    void InputAction(SDL_Renderer *renderer, SDL_Event events);
    void clips();
    bool Move(Map &map_data);
    bool checkPlayer(Map &map_data);
    void UpdatePlayer(SDL_Renderer* renderer);

    void set_default();

//    bool check_touching(Obstacle &a);

    SDL_Rect getRect();
    bool died;

private:

    int width_frame, height_frame;
    SDL_Rect frame_clips[13];
    Input input_type;
    int frame, status;
    bool StandOnGround;

};


#endif // PENGUIN_H_INCLUDED
