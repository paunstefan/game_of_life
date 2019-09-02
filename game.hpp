#include <cstdint>
#include <vector>

/**
	My simple implementation of Conway's Game of Life in C++
*/

class Game{
private:
	uint32_t rows;
	uint32_t cols;
	std::vector<std::vector<bool>> present_board;
	std::vector<std::vector<bool>> future_board;
	uint32_t generation;
public:
	Game(uint32_t r, uint32_t c);
	~Game();
	/**
		Method to display the present_board.
	*/
	void displayBoard();

	/**
		Counts a given cell's neighbors.
		@param row: the row
		@param col: the column
		@return the number of neighbors
	*/
	uint32_t neighbors(uint32_t row, uint32_t col);

	/**
		Inceremnts the game 1 generation.
	*/
	void evolve();

	/**
		Runs the game for a given number of generations, showing them all on the terminal.
		@param generations: number of generations
	*/
	void run(uint32_t generations);
};