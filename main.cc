#include <iostream>
#include <string>
#include "tview.h"
#include "view.h"
#include "model.h"
#include "human.h"

using namespace std;



int main() {
	Tview v;
	Model m(&v);
	
	Human h(m.get_snake());

	v.show();
	
	v.paint(m.get_rabbits());
	v.paint(m.get_snake());
	//m.tick(100000);
	v.run_loop();
	//getchar();
	return 0;
}
