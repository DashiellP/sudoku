#include "GameMaster.h"
#include "Board.h"
#include <iostream>

GameMaster::GameMaster()
{
}

void GameMaster::startGame()
{
	this->_board = new Board(9, 9, 3, 3);
	int x, y, value;
	while (!this->isGameComplete())
	{
		std::cout << this->_board->toString();
		std::cout << "x: ";
		std::cin >> x;
		std::cout << "y: ";
		std::cin >> y;
		std::cout << "value: ";
		std::cin >> value;
		this->_board->writeValueToBoard(value, x, y);
	}
	std::cout << "COMPLETE";
}

bool GameMaster::makeMove(int value, int x, int y)
{
	return this->_isValidMove(value, x, y) && this->_board->writeValueToBoard(value, x, y);
}

bool GameMaster::isGameComplete()
{
	std::vector<BoardSquare> boardState = this->_board->getBoardState();
	for (std::vector<BoardSquare>::iterator it = boardState.begin(); it != boardState.end(); ++it)
	{
		if (it->getValue() == 0) return false;
	}
	return true;
}

bool GameMaster::_isValidMove(int value, int x, int y)
{
	std::list<int> validValues = this->_board->getValidValuesForCoordinates(x, y);
	return std::find(validValues.begin(), validValues.end(), value) != validValues.end();
}