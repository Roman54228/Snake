#pragma once

#include <iterator>
#include <ctime>
#include <iostream>
#include <list>
#include <unistd.h>


using namespace std;

class View;

struct Coord
{
    int x;
    int y;
};

class Rabbit
{
public:
    Rabbit(int x, int y);
    Coord get_coord() const;
private:
    Coord c;
};

enum Direction {LEFT, RIGHT, UP, DOWN};

class Snake
{
public:
    Snake();
    Snake(Coord begin, int len);
    list<Coord> get_body() const;
    Coord get_head() const;
    Coord get_tail() const;
    Direction get_direct() const;
    void erase_tail();
    void push_cell(Coord c);
    void inc_dec_head(string flag, char obj);
    void inc_dec_tail(string flag, char obj);
    void change_dir(Direction direction);
private:
    list<Coord> body;
    Coord head;
    Direction direct;
};

class Model
{
public:
    Model(View* myview);
    list<Rabbit> get_rabbits();
    Snake* get_snake();
    void tick(int interval);
    void key_pressed(int key);
private:
    View* view;
    list<Rabbit> rabbits;
    Snake snake;
    void updatestate(Snake& s);
    void updatestate(list<Rabbit>& r);
    list<Rabbit>::const_iterator find_rabbit(Coord coord);
};
