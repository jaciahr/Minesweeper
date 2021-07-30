#pragma once

#include <vector>
#include "Tile.h"
#include <SFML/Graphics.hpp>
using namespace std;

class Board {
	unsigned int columns;
	unsigned int rows;
	unsigned int bombCount;
	bool win;
	
public:
	vector<vector<Tile>> gameBoardVector;
	vector<Tile> gameBoardSubVector;
	Board(unsigned int mineCount, unsigned int blocksWidth, unsigned int blocksLength);
	void CalculateNeighbors(unsigned int blocksWidth, unsigned int blocksHeight);
	void MineTime(unsigned int& mineCount, unsigned int& blocksWidth, unsigned int& blocksHeight);
	void RecursiveReveal(Tile& tile, bool gameStatus);
	bool GameWin(unsigned int mineCount, unsigned int blocksWidth, unsigned int blocksHeight);
};