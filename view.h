#pragma once
#include "model.h"
#include <functional>
class View
{
public:
    using timer_fn = function<void(int)>;
    using key_fn = function<void(int)>;
    View(){}
    virtual void show(void) = 0;
    virtual void paint(const Rabbit& r) = 0;
    virtual void paint(const Snake* s) = 0;
    virtual void paint(const Coord& c, string obj, string color) = 0;
    virtual void clear(const Coord& c) = 0;
    virtual int get_col() = 0;
    virtual int get_row() = 0;


    virtual void on_timer(timer_fn f, int timer) = 0;
    virtual void run_loop() = 0;
    virtual void on_key(key_fn f) = 0;
    virtual void quit() = 0;




};
