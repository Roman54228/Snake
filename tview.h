
#pragma once
#include <termios.h>
#include <unistd.h>
#include <utility>
#include <string>
#include <cstdio>
#include <functional>
#include <signal.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/ioctl.h>
#include "view.h"

using namespace std;

class Tview : public View
{
public:
    Tview();
    ~Tview();
    void show();
    void paint(const Rabbit& rabbit);
    void paint(const list<Rabbit>& rabbits);
    void paint(const Snake* snake);
    void paint(const Coord& c, string obj, string color);
    void clear(const Coord& c);
    int get_row();
    int get_col();
    void on_timer(timer_fn f, int timer);
    void run_loop();
    void on_key(key_fn f);
    void quit();

private:
    list<key_fn> on_key_list;
    bool finished;
    int row;
    int col;
    struct termios old;
    int      timer_time;
    timer_fn timer_func;
    void draw_set_winsize();
    void draw_set_color(string color);
    void draw_default_color();
    void draw_string(int x, int y, string str);
    void draw(int x, int y, int col, int row);
    void draw_v_line(int x, int y, int len);
    void draw_g_line(int x, int y, int len);
    void draw_frame();
    void draw_go_to(int x, int y);
    void draw_clear_all();

    
    
};


