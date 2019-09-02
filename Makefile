CXX=g++
CFLAGS=-Wall
OBJ = main.cpp game.cpp

gol: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)
