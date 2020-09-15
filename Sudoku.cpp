// Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include "GameMaster.h"
#include "SudokuConsoleInterface.h"

int main()
{
	SudokuConsoleInterface interface = SudokuConsoleInterface();
	interface.startGame();
}