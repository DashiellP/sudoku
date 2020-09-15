#pragma once
#include "GameMaster.h"

class SudokuConsoleInterface
{
public:
	void startGame();
private:
	GameMaster* _gameMaster;
	void _runGame();
	void _printBoard();
};

