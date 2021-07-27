#include "Board.h"
#include "Random.h"
#include <iostream>
#include "TextureManager.h"
#include "Tile.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;



Board::Board(unsigned int blocksWidth, unsigned int blocksHeight) {
    for (unsigned int i = 0; i < blocksWidth; i++) {
        for (unsigned int j = 0; j < blocksHeight; j++) {
            Tile newTile;
            gameBoardSubVector.push_back(newTile);
        }
        gameBoardVector.push_back(gameBoardSubVector);
        gameBoardSubVector.clear();
    }
    /*gameBoardVector.resize(boardWidth, boardHeight);
    for (int i = 0; i < boardWidth; i++) {
        vector<Tile> gameBoardVector;
        for (int j = 0; j < boardHeight; j++) {
            Tile tile;
            gameBoardVector[i].push_back(tile);
        }
    }*/
}


void Board::CalculateNeighbors(Board board, unsigned int blocksWidth, unsigned int blocksHeight) {
    for (unsigned int i = 0; i < blocksWidth; i++) {
        for (unsigned int j = 0; j < blocksHeight; j++) {
            if ((i == 0) && (j == 0)) {
                board.gameBoardVector.at(1).at(0).neighbors.push_back(&this->tiles[i + 1][j])
                    neighborCounter++;
                }
                if
            }
        }
    }
}
