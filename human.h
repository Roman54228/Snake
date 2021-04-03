
#include "view.h"
#include "model.h"


class Human
{
public:

	Human(Snake *s);
	void onKey(int key);
private:
	Snake *snake;
};
