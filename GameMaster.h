#pragma once
#include "Board.h"
class GameMaster
{
private:
	Board* _board;
	bool _isValidMove(int value, int x, int y);

public:
	GameMaster();
	void startGame(int numberOfStartingValues);
	bool makeMove(int value, int x, int y);
	bool isGameComplete();
	Board getBoard();
};

