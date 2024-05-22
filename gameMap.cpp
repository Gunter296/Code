#include "gameMap.h"

GameMap::GameMap()
{
    game_map.max_x=0;
    game_map.max_y=0;
}

void GameMap::LoadMap(char* name)
{
    fstream file;
    file.open(name);
    if(!file.is_open())
    {
        logErrorAndExit("Can't file", SDL_GetError());
        return;
    }

    for(int i=0; i<MAX_MAP_Y; i++)
    {
        for(int j=0; j<MAX_MAP_X; j++)
        {
            file >> game_map.tile[i][j];
            int val = game_map.tile[i][j];
            if(val > 0)
            {
                if(j > game_map.max_x)
                {
                    game_map.max_x = j;
                }
                if(i> game_map.max_y)
                {
                    game_map.max_y = i;
                }
            }
        }
    }
    game_map.max_x = game_map.max_x + 3;
    game_map.max_y = game_map.max_y + 1;

    game_map.filename = name;
    file.close();
}



void GameMap::LoadTile(SDL_Renderer* renderer_)
{
    fstream file;
    //

    for(int i=0; i<=Max_Tile; i++)
    {
        stringstream address;
        address << "photo\\map\\MapTile\\" << i << ".png";
        string fileName;
        address >> fileName;
        file.open(fileName.c_str());
        if(!file.is_open())
        {
            continue;
        }

        file.close();
        if(!tile_map[i].loadImage(fileName.c_str(), renderer_) )
        {
            logErrorAndExit("Can't Tile Map", SDL_GetError());
        }
    }
}



void GameMap::DrawMap(SDL_Renderer* renderer_)
{
    for(int i = 0; i < MAX_MAP_Y; i++)
    {
        for(int j = 0; j< MAX_MAP_X; j++)
        {
             int val = game_map.tile[i][j];
             if(val > 0)
             {
                 tile_map[val].setDest(j*TILE_SIZE, i*TILE_SIZE);
                 tile_map[val].Draw(renderer_);
             }
        }
    }
}

