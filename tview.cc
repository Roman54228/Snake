#include "tview.h"
#include <poll.h>

#define ESC "\033"

using namespace std;



Tview::Tview()
{
    draw_set_winsize();
	struct termios termios_p;
	tcgetattr(0, &termios_p);
	old = termios_p;
	cfmakeraw(&termios_p);
	tcsetattr(0, TCSAFLUSH, &termios_p);
}

Tview::~Tview()
{
	tcsetattr(0, TCSAFLUSH, &old);
}

void Tview::draw_set_winsize()
{
    struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    col = win.ws_col;
    row = win.ws_row;
}

int Tview::get_row()
{
    return row;
}

int Tview::get_col()
{
    return col;
}



void Tview::draw(int x, int y, int col, int row)
{
    printf(ESC "[32;1m");
    draw_go_to(x, y);
    for (int i = 0; i <= col; i++)
    {
        printf("*");
    }

    for (int i = 1; i <= row+2; i++)
    {
        draw_go_to(x, i);
        printf("*");
        draw_go_to(col, i);
        printf("*");
    }
    draw_go_to(x, row+2);
    for (int i = 0; i <= col; i++)
    {
        printf("*");
    }



}

void Tview::draw_frame()
{
    draw(0, 2, col, row);


    /*draw_g_line(0, 0, col);
    draw_g_line(0, row, col);
    draw_string(0, 0, "+");
    draw_string(col, 0, "+");
    draw_string(col, row, "+");
    draw_string(0, row, "+");*/
}

void Tview::draw_string(int x, int y, string str)
{
    draw_go_to(x, y);
    cout << str;
}

void Tview::draw_go_to(int x, int y)
{
    printf(ESC "[%d;%dH", y, x);
}

void Tview::draw_clear_all()
{
    printf(ESC "[H");
    printf(ESC "[J");
}

void Tview::draw_set_color(string color)
{
    if (color == "r")
    {
        printf(ESC "[31;1m");
    }
    else if (color == "green")
    {
        printf(ESC "[32;1m");
    }
    else if (color == "y")
    {
        printf(ESC "[33;1m");
    }
    else if (color == "b")
    {
        printf(ESC "[34;1m");
    }
    else if (color == "gray")
    {
        printf(ESC "[30;1m");
    }
}

void Tview::draw_default_color()
{
    printf(ESC "[0m");
}

void Tview::paint(const Rabbit& rabbit)
{
    Coord c = rabbit.get_coord();
    draw_set_color("green");
    draw_string(c.x, c.y, "@");
}

void Tview::paint(const list<Rabbit>& rabbits)
{
    for (Rabbit item : rabbits)
    {
        paint(item);
    }
}

void Tview::paint(const Snake* snake)
{
    draw_set_color("green");
    draw_string(snake->get_tail().x, snake->get_tail().y, "x");
    for (Coord c : snake->get_body())
    {
        draw_string(c.x, c.y, "x");
    }
    Coord head = snake->get_head();
    switch(snake->get_direct())
    {
        case LEFT:
            draw_string(head.x, head.y, "1");
            break;
        case RIGHT:
            draw_string(head.x, head.y, "<");
            break;
        case UP:
            draw_string(head.x, head.y, "^");
            break;
        case DOWN:
            draw_string(head.x, head.y, "v");
            break;
    }
    draw_default_color();
}

void Tview::paint(const Coord& c, string obj, string color)
{
    draw_set_color(color);
    draw_string(c.x, c.y, obj);
    draw_default_color();
}

void Tview::clear(const Coord& c)
{
    draw_string(c.x, c.y, " ");
}

void repaint(const Snake& snake)
{

}

void Tview::show()
{
    setbuf(stdout, NULL);
    draw_clear_all();
    draw_set_winsize();
    draw_frame();
}

void Tview::on_timer(timer_fn f, int time)
{
    timer_time = time;
    timer_func = f;
}

void Tview::on_key(key_fn f)
{
    on_key_list.push_back(f);
}

void Tview::quit()
{
    finished = true;
}

void Tview::run_loop()
{
    finished = false;
    struct pollfd fds[] = { {0, POLLIN, 0} };
    while(!finished)
    {
        usleep(timer_time*1000);
        timer_func(1);
	int n = poll(fds, 1, timer_time);
	if (n != 0)
	{
		char buf[1];
		read(0, buf, 1);
		for (auto f : on_key_list)
		{
			f(buf[0]);
		}
	}
    }
}
