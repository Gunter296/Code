#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED

#include "Graphic.h"
#include "LoadImage.h"


#define Max_Tile 36


/********************************************************/

// address: "E:\\SDLfirst\\myGame\\photo\\map\\TileMap"

/*******************************************************/

class TileMap : public Image
{
    public:
        TileMap () {}
        ~TileMap () {}
};

class GameMap
{
    public:
        GameMap();
        ~GameMap() {}
        void LoadMap(char* name);
        void LoadTile(SDL_Renderer* renderer_);
        void DrawMap(SDL_Renderer* renderer_);
        void FreeMap()
        {
            for(int i=0; i<Max_Tile; i++)
            {
                tile_map[i].Free();
            }
        }
        Map getMap() const  {return game_map;}
    private:
        Map game_map;
        TileMap tile_map[Max_Tile];

};

#endif // GAMEMAP_H_INCLUDED
