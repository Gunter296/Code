#include "Obstacle.h"

void Obstacle::set_default()
{
    dy = 0;
    dx = throw_speed;
    x = 0;
    y = -64;
    width_frame = 0;
    height_frame = 0;
    status = 1;
    frame = 0;
}

Obstacle::Obstacle()
{
    dy = 0;
    dx = throw_speed;
    x = 0;
    y = -64;
    width_frame = 0;
    height_frame = 0;
    status = 1;
    frame = 0;
}

bool Obstacle::load_obstacle(const char* filename, SDL_Renderer* renderer)
{
    bool res = loadImage(filename, renderer);
    if(res)
    {
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        width_frame = dest.w / FRAME;
        height_frame = dest.h;
    }
    return res;
}

void Obstacle::show(SDL_Renderer *renderer)
{
    if(status==0)
    {
        load_obstacle("photo\\Obstacle\\Snowball\\Snowball_right_60_60.png", renderer);
            if( width_frame > 0 && height_frame > 0 )
        {
            for(int i=0; i<FRAME; i++)
            {
                frame_clips[i].x = i*width_frame;
                frame_clips[i].y = 0;
                frame_clips[i].w = width_frame;
                frame_clips[i].h = height_frame;
            }
        }
    }
    else
    {
        load_obstacle("photo\\Obstacle\\Snowball\\Snowball_left_60_60.png", renderer);
        if( width_frame > 0 && height_frame > 0 )
        {
            for(int i=FRAME-1; i>=0; i--)
            {
                frame_clips[i].x = i*width_frame;
                frame_clips[i].y = 0;
                frame_clips[i].w = width_frame;
                frame_clips[i].h = height_frame;
            }
        }
    }
    frame++;
    if(frame>= FRAME) frame = 0;
    dest.x = x;
    dest.y = y;
    SDL_Rect *current_clips = &frame_clips[frame];

    SDL_Rect renderQuad = { dest.x, dest.y, width_frame, height_frame };
    SDL_RenderCopy (renderer, texture, current_clips, &renderQuad);
}

SDL_Rect Obstacle::getRect()
{
    SDL_Rect rect = {dest.x, dest.y, width_frame, height_frame};
    return rect;
}

bool Obstacle::Move()
{
    if(status == 0)
    {
        dx+= throw_speed;
        if(dx>=max_throw_speed)
        {
            dx = max_throw_speed;
        }
        if(x>MAX_MAP_X*TILE_SIZE)
        {
            Free();
            return false;
        }
    }else
    {
        dx -= throw_speed;
        if( dx <= negative_max_speed )
        {
            dx = negative_max_speed;
        }
        if( x < 0 )
        {
            Free();
            return false;
        }
    }
    x+=dx;
    return true;
}



void Obstacle::Random_throw(Map  &map_data)
{
    int throw_x, throw_y, y_limit = MAX_MAP_Y/2 - 2;
    srand((int) time(NULL));
    int chance_x = rand() % 101;
    if(chance_x<50)
    {
        throw_x = 0;
        status = 0;
    }else
    {
        throw_x = (MAX_MAP_X-1);
        status = 1;
    }
    int chance_y = rand() % y_limit;
    switch(chance_y)
    {
    case 0:
        {
            throw_y = (chance_y + 5)*TILE_SIZE;
            break;
        }
    case 1:
        {
            throw_y = (chance_y + 5)*TILE_SIZE;
            break;
        }
    case 2:
        {
            throw_y = (chance_y + 5)*TILE_SIZE;
            break;
        }
    }
    x = throw_x*TILE_SIZE;
    y = throw_y;

}

