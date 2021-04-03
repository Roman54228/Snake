#include "human.h"



Human::Human(Snake *s)
{
	snake = s;

}


void Human::onKey(int key)
{

switch(key)
{
	case 'a':
		snake->change_dir(LEFT);
		break;
		


}


}
