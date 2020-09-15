#pragma once

#include <set>

class Board;

class BoardSquare
{
private:
	int _x;
	int _y;
	int _value;
	Board *_board;
	std::set<int> _valuesAttemptedDuringBoardGeneration;

public:
	bool isMutable;

	BoardSquare();
	BoardSquare(Board *board, int x, int y);

	std::set<int> getAttemptedValues();
	int getX();
	int getY();
	int getValue();

	void clearAttemptedValues();
	bool assignValue(int value, bool boardIsGenerating);
};

