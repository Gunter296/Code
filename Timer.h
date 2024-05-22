#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "Graphic.h"

const int FPS = 30;


class Time
{
public:
    Time();
    ~Time() {}
    void start();
    void stop();
    void pause();
    void unpause();
    int get_tick();
    bool started();
    bool paused();

    int get_start_tick () {return start_tick;}

private:
    int start_tick, pause_tick;
    bool is_paused, is_started;
};

#endif // TIMER_H_INCLUDED
