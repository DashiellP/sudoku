#include "Square.h"
#include <set>

BoardSquare::BoardSquare() :
	_x(-1), _y(-1), _board(nullptr), _value(0) {}

BoardSquare::BoardSquare(Board *board, int x, int y)
{ 
	this->_board = board;
	this->_x = x;
	this->_y = y;
	this->_valuesAttemptedDuringBoardGeneration = std::set<int>();
	this->_value = 0;
}

std::set<int> BoardSquare::getAttemptedValues() { return this->_valuesAttemptedDuringBoardGeneration; }
int BoardSquare::getX() { return this->_x; }
int BoardSquare::getY() { return this->_y; }
int BoardSquare::getValue() { return this->_value; }

void BoardSquare::clearAttemptedValues()
{
	this->_valuesAttemptedDuringBoardGeneration = std::set<int>();
}

bool BoardSquare::assignValue(int value, bool boardIsGenerating)
{
	if (boardIsGenerating)
	{
		this->_valuesAttemptedDuringBoardGeneration.insert(value);
		this->_value = value;
		this->isMutable = value == 0;
		return true;
	}
	else if (this->_value == 0 || this->isMutable)
	{
		// If the board isn't being generated (i.e., play has started),
		// we can only assign a value if the square is empty or was not filled
		// during board generation
		this->_value = value;
		return true;
	}
	return false;
}