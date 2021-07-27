#pragma once

#include <vector>
#include "Tile.h"
#include <SFML/Graphics.hpp>
using namespace std;

class Board {
	unsigned int columns;
	unsigned int rows;
	unsigned int bombCount;
	
public:
	vector<vector<Tile>> gameBoardVector;
	vector<Tile> gameBoardSubVector;
	Board(unsigned int blocksWidth, unsigned int blocksLength);
	int neighborCounter = 0;
	void CalculateNeighbors(Board board, unsigned int blocksWidth, unsigned int blocksHeight);
};