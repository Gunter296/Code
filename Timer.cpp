#include "Timer.h"

Time::Time()
{
    start_tick=0;
    pause_tick=0;
    is_paused=0;
    is_started=0;
}

void Time::start()
{
    is_started = 1;
    is_paused = 0;
    start_tick = SDL_GetTicks();
}

void Time::stop()
{
    is_paused = 0;
    is_started = 0;
}

void Time::pause()
{
    if(is_started==1 && is_paused==0)
    {
        is_paused = 1;
        pause_tick = SDL_GetTicks() - start_tick;
    }
}

void Time::unpause()
{
    if(is_paused==1)
    {
        is_paused==0;
        start_tick = SDL_GetTicks() - pause_tick;
        pause_tick = 0;
    }
}

int Time::get_tick()
{
    if(is_started==1)
    {
        if(is_paused==1)
        {
            return pause_tick;
        }
        else{
            return SDL_GetTicks() - start_tick;
        }
    }
    return 0;
}

bool Time::started()
{
    return is_started;
}

bool Time::paused()
{
    return is_paused;
}
