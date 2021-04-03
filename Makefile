OBJ = tview.o main.o model.o human.o
EXE = snake

CC=g+++
CFLAGS=-c -Wall

all: $(EXE) 

$(EXE): $(OBJ)
	$(CXX) -o $(EXE) $(OBJ) $(CXXFLAGS)
clean:
	$(RM) $(OBJ) $(EXE)
tview.o : tview.h
depend:
	$(CXX) -MM $(OBJ:.o=.cc) >.depend

-include .depend
