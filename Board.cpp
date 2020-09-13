#include "Board.h"
#include "Square.h"
#include <stdlib.h>
#include <list>
#include <string>
#include <time.h>
#include <math.h> 
#include <iostream>
#include <random>

Board::Board(int width, int height, int boxWidth, int boxHeight)
    {
        this->_width = width;
        this->_height = height;
        this->_boxWidth = boxWidth;
        this->_boxHeight = boxHeight;
        this->_generateSolvedBoard();
    }

    /*int Board::getWidth();
    int Board::getHeight();
    int Board::getBoxWidth();
    int Board::getBoxHeight();
    int Board::getValueAtCoordinates(int x, int y);
    int* Board::getValuesInColumn(int x);
    int* Board::getValuesInRow(int y);
    int* Board::getValuesInBox(int x, int y);*/

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

    std::list<int> Board::getValidValuesForCoordinates(int x, int y)
    {
        std::list<int> validValues = std::list<int>({1, 2, 3, 4, 5, 6, 7, 8, 9});
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

    bool Board::writeValueToBoard(int value, int x, int y)
    {
        this->_boardState[this->_width * y + x].assignValue(value, false);
        return true;
    }

    std::string Board::toString()
    {
        // The output contains 1 character per box + the borders + a newline character for each line
        int outputWidth = this->_width * 2 + 2;
        int outputHeight = this->_height * 2 + 1;
        std::string output = "";
        for (int i = 0; i < this->_width * this->_height; ++i)
        {
            output += std::to_string(this->_boardState[i].getValue());
            if (i % this->_width == this->_width - 1)
            {
                output += '\n';
            }
        }
        return output;
        for (int y = 0; y < outputHeight; ++y)
        {
            for (int x = 0; x < outputWidth; ++x)
            {
                if (x % this->_boxWidth == 0)
                {
                    if (y % this->_boxHeight == 0)
                    {
                        output += "x";
                    }
                    else
                    {
                        output += "x";
                    }
                }
                else
                {
                    if (y % 2 == 0)
                    {
                        output += "x";
                    }
                    else
                    {

                    }
                }
            }
        }
    }

    //int Board::_createBoard();

    int Board::_generateSolvedBoard()
    {
        srand(time(NULL));
        int boardSize = this->_width * this->_height;
        this->_boardState = std::vector<BoardSquare>(boardSize);
        int backsteps = 0;
        for (int y = 0; y < this->_height; ++y)
        {
            for (int x = 0; x < this->_width; ++x)
            {
                int squareIndex = y * this->_width + x;
                std::list<int> validValues = this->getValidValuesForCoordinates(x, y);
                BoardSquare newSquare(this, x, y);
                if (this->_boardState[squareIndex].getAttemptedValues().size() > 0)
                {
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
                    newSquare.assignValue(0, false);
                    newSquare.clearAttemptedValues();
                    this->_boardState[squareIndex] = newSquare;
                    if (x > 0)
                    {
                        x -= 2;
                    }
                    else
                    {
                        x = this->_width - 1;
                        y -= 1;
                    }
                }
                else
                {
                    std::list<int>::iterator randIt = validValues.begin();
                    std::advance(randIt, std::rand() % validValues.size());
                    newSquare.assignValue(*randIt, true);
                    this->_boardState[squareIndex] = newSquare;
                }
            }
        }
        return 1;
    }
