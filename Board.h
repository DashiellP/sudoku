#pragma once
#include <string>
#include <vector>
#include <list>
#include "Square.h"
class Board
{
public:
	Board(int width, int height, int boxWidth, int boxHeight, int numberOfStartingValues);

	int getWidth();
	int getHeight();
	int getBoxWidth();
	int getBoxHeight();
	std::vector<BoardSquare> getBoardState();
    int getValueAtCoordinates(int x, int y);
	std::list<int> getValuesInColumn(int x);
	std::list<int> getValuesInRow(int y);
	std::list<int> getValuesInBox(int x, int y);
	std::list<int> getValidValuesForCoordinates(int x, int y);
	bool writeValueToBoard(int value, int x, int y);
	std::string toString();

private:
	int _width;
	int _height;
	int _boxWidth;
	int _boxHeight;
	std::vector<BoardSquare> _boardState;
	std::vector<int> _solution;

	int _createBoard();
	int _generateSolvedBoard();
	void _unsolveBoard(int numberOfValuesToDelete);
};
