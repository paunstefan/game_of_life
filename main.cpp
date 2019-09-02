#include <iostream>
#include <cstdint>
#include "game.hpp"

void help(){
	printf("Usage: ./gol [rows] [columns] [generations]\n");
}

int main(int argc, char **argv){
	if(argc != 4){
		help();
		exit(1);
	}
	
	uint32_t rows = std::stoi(argv[1]);
	uint32_t cols = std::stoi(argv[2]);
	uint32_t gen = std::stoi(argv[3]);

	Game g(rows, cols);
	g.run(gen);

	return 0;
}