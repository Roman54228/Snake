#include "model.h"
#include "view.h"
#include <memory>
#include <functional>
#include <algorithm>
#include <cmath>
using namespace std::placeholders;
Model::Model(View* myview)
{
    view = myview;
    int col = view->get_col();
    int row = view->get_row();
    srand(time(NULL));
    for (int i = 0; i < 5; ++i)
    {
        int x = rand() % (col - 2) + 1;
        int y = rand() % (row - 2) + 1;
        rabbits.push_back(Rabbit(x, y));
    }
    Coord begin;
    begin.x = col / 2;
    begin.y = row / 2;
    snake = Snake();


    view->on_key(bind(&Model::key_pressed, this, _1));
    view->on_timer(bind(&Model::tick, this, _1), 50);

    //snake = Snake(begin, 10);
}

void Model::key_pressed(int key)
{
   if (key == 'q')
   {
       view->quit();
   }
   if (key == 'a')
   {
	get_snake()->change_dir(RIGHT);

   }
   if (key == 'w')
   {
	   get_snake()->change_dir(UP);
   }
   
   if (key == 's')
   {
	   get_snake()->change_dir(DOWN);

   }
   if(key == 'd')
   {
	get_snake()->change_dir(LEFT);
   }
};

void Model::updatestate(Snake& s)
{
    view->paint(s.get_head(), "x", "green");
    s.push_cell(s.get_head());
    switch (s.get_direct())
    {
        case LEFT:
            s.inc_dec_head("inc", 'x');
            view->paint(s.get_head(), ">", "green");
            break;
        case RIGHT:
            s.inc_dec_head("dec", 'x');
            view->paint(s.get_head(), "<", "green");
            break;
        case UP:
            s.inc_dec_head("dec", 'y');
            view->paint(s.get_head(), "^", "green");
            break;
        case DOWN:
            s.inc_dec_head("inc", 'y');
            view->paint(s.get_head(), "v", "green");
            break;
    }
    /*if (find_rabbit(s.get_head()) == cend(get_rabbits()))
    {
	    view->clear(s.get_tail());
    }*/
    view->clear(s.get_tail());

    s.erase_tail();
}


/*list<Rabbit>::const_iterator Model::find_rabbit(Coord coord)
{
	for (list<Rabbit>::const_iterator it = cbegin(get_rabbits()); it != cend(get_rabbits()); it++)
	{
		if ((*it).get_coord().x == coord.x && (*it).get_coord().y == coord.y)
		{
			return it;
		}
	}
	return cend(get_rabbits());
}*/


void Model::updatestate(list<Rabbit>& rab)
{

}

void Model::tick(int interval)
{
  
        updatestate(snake);
        
       
    
}

list<Rabbit> Model::get_rabbits()
{
    return rabbits;
}

Snake* Model::get_snake()
{
    return &snake;
}

Rabbit::Rabbit(int x, int y)
{
    c.x = x;
    c.y = y;
}

Coord Rabbit::get_coord() const
{
    return c;
}

Snake::Snake()
{
    Coord c = {2, 2};
    for (int j = 0; j <20; ++j)
    {
        body.push_back(c);
        c.x++;
    }
    head = c;
    direct = DOWN;
}

Snake::Snake(Coord begin, int len)
{
    for (int i = 0; i < len; ++i)
    {
        body.push_back(begin);
        begin.x++;
    }
    head = begin;
    direct = DOWN;
}

list<Coord> Snake::get_body() const
{
    return body;
}

Coord Snake::get_head() const
{
    return head;
}

Coord Snake::get_tail() const
{
    list<Coord>::const_iterator it = body.begin();
    return *it;
}

Direction Snake::get_direct() const
{
    return direct;
}

void Snake::change_dir(Direction direct_)
{

	direct = direct_;
}

void Snake::inc_dec_head(string flag, char obj)
{
    if (flag == "inc")
    {
        if (obj == 'x')
        {
            head.x++;
        }
        else if (obj == 'y')
        {
            head.y++;
        }
    }
    else if (flag == "dec")
    {
        if (obj == 'x')
        {
            head.x--;
        }
        else if (obj == 'y')
        {
            head.y--;
        }
    }
}

void Snake::push_cell(Coord c)
{
    body.push_back(c);
}

void Snake::erase_tail()
{
    list<Coord>::iterator it = body.begin();
    body.erase(it);
}


