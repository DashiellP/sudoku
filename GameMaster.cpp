#include "GameMaster.h"
#include "Board.h"
#include <iostream>

GameMaster::GameMaster()
{
}

/*
 Initialize the game board
 */
void GameMaster::startGame(int numberOfStartingValues)
{
	this->_board = new Board(9, 9, 3, 3, numberOfStartingValues);
}

/*
 Write a value to (x,y). Returns true if the value is valid and was successfully written.
 */
bool GameMaster::makeMove(int value, int x, int y)
{
	return 
		this->_isValidMove(value, x, y) && 
		this->_board->writeValueToBoard(value, x, y);
}

bool GameMaster::isGameComplete()
{
	// Check if all squares are filled in. Values are validated on input, but 
	// may want to add validation here too
	std::vector<BoardSquare> boardState = this->_board->getBoardState();
	for (std::vector<BoardSquare>::iterator it = boardState.begin(); it != boardState.end(); ++it)
	{
		if (it->getValue() == 0) return false;
	}
	return true;
}

Board GameMaster::getBoard() { return *this->_board; }

/*
 Check if a given value is valid at (x,y)
 */
bool GameMaster::_isValidMove(int value, int x, int y)
{
	if (value < 0 || value > 9 || 
		x < 0 || x >= this->_board->getWidth() || 
		y < 0 || y >= this->_board->getHeight())
	{
		return false;
	}
	std::list<int> validValues = this->_board->getValidValuesForCoordinates(x, y);
	return std::find(validValues.begin(), validValues.end(), value) != validValues.end();
}