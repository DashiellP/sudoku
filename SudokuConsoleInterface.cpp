#include "SudokuConsoleInterface.h"
#include <iostream>

void SudokuConsoleInterface::startGame()
{
	this->_gameMaster = new GameMaster();
	this->_gameMaster->startGame(16);
	this->_runGame();
}

void SudokuConsoleInterface::_runGame()
{
	int x, y, value;
	while (!this->_gameMaster->isGameComplete())
	{
		if (!std::cin)
		{
			std::cin.clear(); //clear bad input flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		this->_printBoard();
		std::cout << "x (0 - 8): ";
		std::cin >> x;
		std::cout << "y (0 - 8): ";
		std::cin >> y;
		std::cout << "value (1 - 9): ";
		std::cin >> value;
		if (!this->_gameMaster->makeMove(value, x, y))
		{
			std::cout << "Invalid move!" << std::endl;
		}
	}
	this->_printBoard();
	std::cout << "COMPLETE";
}

void SudokuConsoleInterface::_printBoard()
{
	for (int y = 0; y < this->_gameMaster->getBoard().getHeight(); ++y)
	{
		for (int x = 0; x < this->_gameMaster->getBoard().getWidth(); ++x)
		{
			int value = this->_gameMaster->getBoard().getValueAtCoordinates(x, y);
			if (value != 0)
			{
				std::cout << value << ' ';
			}
			else
			{
				std::cout << '_' << ' ';
			}
			if ((x + 1) % this->_gameMaster->getBoard().getBoxWidth() == 0)
			{
				std::cout << ' ';
			}
		}
		std::cout << std::endl;
		if ((y + 1) % this->_gameMaster->getBoard().getBoxWidth() == 0)
		{
			std::cout << std::endl;
		}
	}
}