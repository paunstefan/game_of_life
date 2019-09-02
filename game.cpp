#include "game.hpp"
#include <random>
#include <cstdint>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

// ASCII escape code to clear the terminal
#define clear_screen() printf("\x1B[2J\x1B[H")
// the dead and alive characters to display
#define alive "█"
#define dead " "

Game::Game(uint32_t r, uint32_t c): rows(r), cols(c), generation(0){
	// using a random number generator for the initial state
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, 10);

	this->present_board.reserve(this->rows);
	for(int i = 0; i < this->rows; i++){
		this->present_board[i].reserve(cols);
	}

	this->future_board.reserve(this->rows);
	for(int i = 0; i < this->rows; i++){
		this->future_board[i].reserve(this->cols);
	}

	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->cols; j++){
			if(uni(rng) < 4){
				this->present_board[i][j] = true;
			}
			else{
				this->present_board[i][j] = false;
			}
		}
	}

	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->cols; j++){
			this->future_board[i][j] = false;
		}
	}
}


Game::~Game() {}

/**
	Method to display the present_board.
*/
void Game::displayBoard(){
	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->cols; j++){
			if(this->present_board[i][j] == true){
				printf(alive);
			}
			else{
				printf(dead);
			}
		}
		printf("\n");
	}

}

/**
	Counts a given cell's neighbors.
	@param row: the row
	@param col: the column
	@return the number of neighbors
*/
uint32_t Game::neighbors(uint32_t row, uint32_t col){
	uint32_t n = 0;
	// iterate over all neighboring cells
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			if( !(i == 0 && j == 0)
				&& !(row + i < 0) && !(row + i > this->rows -1)
				&& !(col + j < 0) && !(col + j > this->cols -1)
				&& (this->present_board[row + i][col + j] == true)){
				n++;
			}
		}
	}
	return n;
}


/**
	Inceremnts the game 1 generation.
*/
void Game::evolve(){
	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->cols; j++){
			// apply the Game of Life rules
			// alive
			if(this->present_board[i][j] == true){
				if(this->neighbors(i,j) < 2){
					this->future_board[i][j] = false;
				}
				else if((this->neighbors(i,j) == 2) || (this->neighbors(i,j) == 3)){
					this->future_board[i][j] = true;
				}
				else{
					this->future_board[i][j] = false;
				}
			}
			//dead
			else{
				if(this->neighbors(i,j) == 3){
					this->future_board[i][j] = true;
				}
				else{
					this->future_board[i][j] = false;
				}
			}
		}
	}

	// swap the boards, done to avoid copying the matrix
	this->future_board.swap(this->present_board);

	this->generation++;

}

/**
	Runs the game for a given number of generations, showing them all on the terminal.
	@param generations: number of generations
*/
void Game::run(uint32_t generations){
	clear_screen();
	while(this->generation < generations){
		this->displayBoard();
		this->evolve();
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		clear_screen();
	}
}