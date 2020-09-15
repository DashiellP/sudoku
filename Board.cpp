#include "Board.h"
#include "Square.h"
#include <stdlib.h>
#include <list>
#include <string>
#include <time.h>
#include <math.h> 
#include <iostream>
#include <random>

Board::Board(int width, int height, int boxWidth, int boxHeight, int numberOfStartingValues)
    {
        this->_width = width;
        this->_height = height;
        this->_boxWidth = boxWidth;
        this->_boxHeight = boxHeight;
        // Start by building the solution, then delete values from it
        this->_generateSolvedBoard();
		int numberOfValuesToDelete = width * height - numberOfStartingValues;
        this->_unsolveBoard(numberOfValuesToDelete);
    }

int Board::getValueAtCoordinates(int x, int y)
{
    int i = this->_width * y + x;
    if (i >= this->_width * this->_height) return -1;
    return this->_boardState[i].getValue();
}

std::list<int> Board::getValuesInRow(int y)
{
    std::list<int> output(this->_width);
    for (int x = 0; x < this->_width; ++x)
    {
        output.push_back(this->getValueAtCoordinates(x, y));
    }
    return output;
}

std::list<int> Board::getValuesInColumn(int x)
{
    std::list<int> output(this->_width);
    for (int y = 0; y < this->_height; ++y)
    {
        output.push_back(this->getValueAtCoordinates(x, y));
    }
    return output;
}

std::list<int> Board::getValuesInBox(int x, int y)
{
    int firstTileInBoxX = floor(x / this->_boxWidth) * this->_boxWidth;
    int firstTileInBoxY = floor(y / this->_boxHeight) * this->_boxHeight;
    std::list<int> output(this->_width);
    for (int i = 0; i < this->_boxHeight; ++i)
    {
        for (int j = 0; j < this->_boxWidth; ++j)
        {
            output.push_back(this->getValueAtCoordinates(firstTileInBoxX + j, firstTileInBoxY + i));
        }
    }
    return output;
}

std::vector<BoardSquare> Board::getBoardState() { return this->_boardState; }
int Board::getWidth() { return this->_width; }
int Board::getHeight() { return this->_height; }
int Board::getBoxWidth() { return this->_boxWidth; }
int Board::getBoxHeight() { return this->_boxHeight; }

/*
 Get the values that can be written at (x, y) that do not conflict with those already on the board
 */
std::list<int> Board::getValidValuesForCoordinates(int x, int y)
{
	std::list<int> validValues = std::list<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
	std::list<int> valuesOnBoard = this->getValuesInColumn(x);
	valuesOnBoard.splice(valuesOnBoard.end(), this->getValuesInRow(y));
	valuesOnBoard.splice(valuesOnBoard.end(), this->getValuesInBox(x, y));
	std::list<int>::iterator it = valuesOnBoard.begin();
	for (std::list<int>::iterator iterator = valuesOnBoard.begin(), end = valuesOnBoard.end();
		iterator != end;
		++iterator)
	{
		validValues.remove(*iterator);
	}
	return validValues;
}

/*
 Attempt to write a value to (x,y). Returns true if the value is valid and was successfully written.
 */
bool Board::writeValueToBoard(int value, int x, int y)
{
	return this->_boardState[this->_width * y + x].assignValue(value, false);
}

/*
 Initialize the _boardState property and populate it with a randomly generated, solved board
 */
int Board::_generateSolvedBoard()
{
	srand(time(NULL));
	int boardSize = this->_width * this->_height;
	this->_boardState = std::vector<BoardSquare>(boardSize);
	for (int y = 0; y < this->_height; ++y)
	{
		for (int x = 0; x < this->_width; ++x)
		{
			int squareIndex = y * this->_width + x;
			std::list<int> validValues = this->getValidValuesForCoordinates(x, y);
			BoardSquare newSquare(this, x, y);
			if (this->_boardState[squareIndex].getAttemptedValues().size() > 0)
			{
				// If we have tried assigning values to the square before,
				// Remove them from the possible values for this square
				newSquare = this->_boardState[squareIndex];
				if (validValues.size() > 0)
				{
					std::set<int> attemptedValues = newSquare.getAttemptedValues();
					for (std::set<int>::iterator it = attemptedValues.begin(); it != attemptedValues.end(); ++it)
					{
						validValues.remove(*it);
					}
				}
			}
			if (validValues.size() == 0)
			{
				// If there are no valid values for this square, step back 1 square
				// And try assigning a new value to it
				newSquare.assignValue(0, true);
				newSquare.clearAttemptedValues();
				this->_boardState[squareIndex] = newSquare;
				if (x > 0)
				{
					x -= 2;
				}
				else
				{
					// Step back to the end of the previous line if necessary
					x = this->_width - 1;
					y -= 1;
				}
			}
			else
			{
				// Assign a random valid value to the square
				std::list<int>::iterator randIt = validValues.begin();
				std::advance(randIt, std::rand() % validValues.size());
				newSquare.assignValue(*randIt, true);
				this->_boardState[squareIndex] = newSquare;
			}
		}
	}
	return 1;
}

/*
 Delete a given number of randomly selected values from the board
 */
void Board::_unsolveBoard(int numberOfValuesToDelete)
{
	// Shuffle the squares on the board and erase the values from the first several
	std::vector<BoardSquare> tempBoard = this->_boardState;
	std::random_shuffle(tempBoard.begin(), tempBoard.end());
	std::vector<BoardSquare>::iterator it = tempBoard.begin();
	int i = 0;
	while (i < numberOfValuesToDelete && it != tempBoard.end())
	{
		this->_boardState[this->_width * it->getY() + it->getX()].assignValue(0, true);
		it->isMutable = true;
		++it;
		++i;
	}
}
