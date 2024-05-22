#include "LoadImage.h"

//Image::~Image(){}
Image::Image()
{
    texture = NULL;
    dest.x = 0;
    dest.y = 0;
    dest.w = 0;
    dest.h = 0;
}

void Image::Free(){
    if(texture!=NULL)
    {
        SDL_DestroyTexture(texture);
        texture  = NULL;
    }
}

//-------------------------------------------------------------------------------------

bool Image::loadImage(const char* filename, SDL_Renderer* renderer)
{
    Free();
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    /*SDL_Surface* surface = IMG_Load(filename);

    if(surface!=NULL)
    {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,198,201,222));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }*/

    texture = IMG_LoadTexture(renderer, filename);

    if (texture == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
        return false;
    }
    else
    {
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        return true;
    }
}

bool Image::createImage(SDL_Renderer* renderer)
{
    if( texture == NULL ) return false;
    SDL_RenderCopy( renderer, texture, NULL, NULL );
    return true;
}


//--------------------------------------------------------------------------------------

void Image::Draw(SDL_Renderer *renderer,  SDL_Rect* clip)
{

    SDL_Rect renderQuad = {dest.x, dest.y, dest.w, dest.h};
    SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}
