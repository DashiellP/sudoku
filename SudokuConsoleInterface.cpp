#include "SudokuConsoleInterface.h"
#include <iostream>

void SudokuConsoleInterface::startGame()
{
	this->_gameMaster = new GameMaster();
	int numberOfStartingValues;
	std::cout << "How many numbers should the board start with? ";
	while (!(std::cin >> numberOfStartingValues))
	{
		// Clear the input if the user entered a non-int value
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	this->_gameMaster->startGame(numberOfStartingValues);
	this->_runGame();
}

/*
 Handle the main game loop. Runs until the game is complete.
 */
void SudokuConsoleInterface::_runGame()
{
	int x, y, value;
	while (!this->_gameMaster->isGameComplete())
	{
		if (!std::cin)
		{
			// Clear the input if the user entered a non-int value
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		this->_printBoard();
		std::cout << "x (1 - 9): ";
		std::cin >> x;
		std::cout << "y (1 - 9): ";
		std::cin >> y;
		std::cout << "value (1 - 9): ";
		std::cin >> value;
		if (!this->_gameMaster->makeMove(value, x-1, y-1))
		{
			std::cout << std::endl << "Invalid move!" << std::endl;
		}
	}
	this->_printBoard();
	// Display an appropriately satisfying victory message
	std::cout << "*   *  * ** *** congratulations you've done it *** ** *  *   *" << std::endl;
}

void SudokuConsoleInterface::_printBoard()
{
	std::cout << std::endl;
	for (int y = 0; y < this->_gameMaster->getBoard().getHeight(); ++y)
	{
		for (int x = 0; x < this->_gameMaster->getBoard().getWidth(); ++x)
		{
			int value = this->_gameMaster->getBoard().getValueAtCoordinates(x, y);
			// Blank spaces have a value of 0
			if (value != 0)
			{
				std::cout << value << ' ';
			}
			else
			{
				std::cout << '_' << ' ';
			}
			// Display an additional space between boxes
			if ((x + 1) % this->_gameMaster->getBoard().getBoxWidth() == 0)
			{
				std::cout << ' ';
			}
		}
		std::cout << std::endl;
		// Display an additional new line between boxes
		if ((y + 1) % this->_gameMaster->getBoard().getBoxWidth() == 0)
		{
			std::cout << std::endl;
		}
	}
}