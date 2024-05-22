#include "Penguin.h"

Character::Character()
{
    dx = 0;
    dy = 0;
    x_pos = 0;
    y_pos = 0;
    width_frame = 0;
    height_frame = 0;
    status = -1;
    input_type.left_ = 0;
    input_type.right_ = 0;
    StandOnGround = false;
    died = false;
}

void Character::set_default()
{
    dx = 0;
    dy = 0;
    x_pos = 0;
    y_pos = 0;
    width_frame = 0;
    height_frame = 0;
    status = -1;
    input_type.left_ = 0;
    input_type.right_ = 0;
    StandOnGround = false;
    died = false;
}

bool Character::load_object_image(const char* filename, SDL_Renderer *renderer)
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

SDL_Rect Character::getRect()
{
    SDL_Rect rect;
    rect.x = dest.x;
    rect.y = dest.y;
    rect.w = width_frame;
    rect.h = height_frame;
    return rect;

}

void Character::clips()
{
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

void Character::show(SDL_Renderer *renderer)
{
    UpdatePlayer(renderer);

    if(input_type.right_ == 1 || input_type.left_ == 1)
    {
        frame++;
    }
    else
    {
        frame = 0;
    }
    if(frame >=  FRAME) frame = 0;

    dest.x = x_pos;
    dest.y = y_pos;


    SDL_Rect *current_clips = &frame_clips[frame];
    SDL_Rect renderQuad = { dest.x, dest.y, width_frame, height_frame };
    if(died==true)
    {
        SDL_SetTextureColorMod(texture, 61, 207, 212);
    }
    SDL_RenderCopy (renderer, texture, current_clips, &renderQuad);
}

void Character::InputAction(SDL_Renderer *renderer, SDL_Event event)
{
    if(died!=true){
    if(event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status = WALK_RIGHT;
                input_type.right_ = 1;
                input_type.left_ = 0;
                UpdatePlayer(renderer);
            }
            break;
        case SDLK_LEFT:
            {
                status = WALK_LEFT;
                input_type.left_ = 1;
                input_type.right_ = 0;
                UpdatePlayer(renderer);
            }
            break;
        default:
            break;
        }
    }else if(event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                input_type.right_ = 0;
            }
            break;
        case SDLK_LEFT:
            {
                input_type.left_ = 0;
            }
            break;
        default:
            break;
        }
    }
    if(event.type == SDL_KEYUP)
    {
        if(event.key.keysym.sym == SDLK_SPACE)
        {
            input_type.jump_ = 1;
        }
    }
    }
}

bool Character::Move(Map &map_data)
{
    if(died!=true){
    dx = 0;
    dy += gravity;
    if(dy >= max_fall)
    {
        dy = max_fall;
    }
    if(input_type.left_ == 1)
    {
        dx -= player_speed;
    }
    if(input_type.right_ == 1)
    {
        dx += player_speed;
    }

    if(input_type.jump_ == 1)
    {
        if(StandOnGround==1)
        {
            dy = - jump_val;
        }
        input_type.jump_ = 0;
        StandOnGround = 0;
    }
    }
    return checkPlayer(map_data);
}

bool Character::checkPlayer(Map &map_data)
{
    if(died!=true){
        int x1 = 0, x2= 0, y1 = 0, y2 = 0;
        int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

        x1 = (x_pos + dx)/TILE_SIZE;
        x2 = (x_pos + dx + width_frame-1)/TILE_SIZE;


        y1 = (y_pos)/TILE_SIZE;
        y2 = (y_pos + height_min)/TILE_SIZE;

        if(x1>=0 && x2<=MAX_MAP_X && y1 >= 0 && y2<MAX_MAP_Y)
        {
            if(dx>0) //rigth
            {
                if(map_data.tile[y1][x2] != Blank || map_data.tile[y2][x2] != Blank)
                {
                    x_pos = x2*TILE_SIZE;
                    x_pos -= width_frame+1;
                    dx = 0;
                }
            }
            if(dx<0) //left
            {
                if(map_data.tile[y1][x1]!= Blank || map_data.tile[y2][x1] != Blank)
                {
                    x_pos = (x1+1)*TILE_SIZE;
                    dx = 0;
                }
            }
        }

        int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
        x1 = (x_pos)/TILE_SIZE;
        x2 = (x_pos + width_min)/TILE_SIZE;

        y1 = (y_pos + dy)/TILE_SIZE;
        y2 = (y_pos + dy + height_frame - 0.5)/TILE_SIZE;


        if(x1>=0 && x2<MAX_MAP_X && y1 >= 0 && y2<MAX_MAP_Y)
        {
            if(dy > 0)
            {
                if(map_data.tile[y2][x1] != Blank || map_data.tile[y2][x2] != Blank)
                {
                    y_pos = y2*TILE_SIZE;
                    y_pos -= height_frame + 1;
                    dy = 0;
                    StandOnGround = true;
                }
            }
            else if(dy < 0)
            {
                if(map_data.tile[y1][x1] != Blank || map_data.tile[y1][x2] != Blank)
                {
                    y_pos = (y1 + 0.2)*TILE_SIZE;
                    dy = 0;
                    StandOnGround = false;
                }
            }
        }
      x_pos += dx;
      y_pos += dy;
      if(x_pos < 0)
      {
          x_pos = 0;
      }
      if(x_pos + width_frame > (map_data.max_x*TILE_SIZE) )
      {
          x_pos = (MAX_MAP_X*TILE_SIZE + 1) - width_frame - 1;
      }
      if((int)y_pos/TILE_SIZE > map_data.max_y)
      {
          return false;
      }
      if( y_pos >= 511 &&( x_pos <835 && x_pos > 390) )
      {
          return false;
      }
      else return true;
    }
    else return false;
}


void Character::UpdatePlayer(SDL_Renderer *renderer)
{
     if(StandOnGround==1){
        if( status == WALK_RIGHT)
        {
            loadImage("photo\\penguin\\penguin_right_60_64.png", renderer);
        }
        else
        {
            loadImage("photo\\penguin\\penguin_left_60_64.png", renderer);
        }
    }
    else if(StandOnGround==0 && dy>=0)
    {
        if( status == WALK_RIGHT)
        {
            loadImage("\photo\\penguin\\penguin_fall_right_60_64.png", renderer);
        }
        else
        {
            loadImage("photo\\penguin\\penguin_fall_left_60_64.png", renderer);
        }
    }
    else
    {
        if( status == WALK_RIGHT)
        {
            loadImage("photo\\penguin\\penguin_jump_right_60_64.png", renderer);
        }
        else
        {
            loadImage("photo\\penguin\\penguin_jump_left_60_64.png", renderer);
        }
    }
}
