#ifndef LOADIMAGE_H_INCLUDED
#define LOADIMAGE_H_INCLUDED

// address: E:\\SDLfirst\\myGame\\photo

#include "Graphic.h"

class Image
{
     public:
         Image ();
         ~Image () {}
        //SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer);

        void setDest(const int x, int y) {
            dest.x = x;
            dest.y = y;
        }
        void Draw(SDL_Renderer* renderer,  SDL_Rect* clip = NULL);

        bool createImage(SDL_Renderer* renderer );
        bool loadImage(const char *filename, SDL_Renderer *renderer);
        void Free();


     public:
        SDL_Texture* texture;
        SDL_Rect dest;
};


#endif // LOADIMAGE_H_INCLUDED
