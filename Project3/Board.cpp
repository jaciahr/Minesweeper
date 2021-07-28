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



Board::Board(unsigned int mineCount, unsigned int blocksWidth, unsigned int blocksHeight) {
    for (unsigned int i = 0; i < blocksWidth; i++) {
        for (unsigned int j = 0; j < blocksHeight; j++) {
            Tile newTile;
            gameBoardSubVector.push_back(newTile);
        }
        gameBoardVector.push_back(gameBoardSubVector);
        gameBoardSubVector.clear();
    }
    MineTime(mineCount, blocksWidth, blocksHeight);
    CalculateNeighbors(blocksWidth, blocksHeight);
}

void Board::MineTime(unsigned int& mineCount, unsigned int& blocksWidth, unsigned int& blocksHeight) {
    unsigned int count = 0;
    unsigned int randomVal1;
    unsigned int randomVal2;
    while (count < mineCount) {
        randomVal1 = Random::Int(0, blocksWidth - 1);
        randomVal2 = Random::Int(0, blocksHeight - 1);
        if (gameBoardVector.at(randomVal1).at(randomVal2).isBomb == false) {
            gameBoardVector.at(randomVal1).at(randomVal2).isBomb = true;
            count++;
        }
    }
}

void Board::CalculateNeighbors(unsigned int blocksWidth, unsigned int blocksHeight) {
    for (unsigned int i = 0; i < blocksWidth; i++) {
        for (unsigned int j = 0; j < blocksHeight; j++) {
            if ((i == 0) && (j == 0)) {
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i).at(j + 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j + 1));
            }
            else if ((i == 0) && (j == (blocksHeight - 1))) {
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i).at(j - 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j - 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j));
            }
            else if ((i == (blocksWidth - 1)) && (j == 0)) {
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i - 1).at(j));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i - 1).at(j + 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i).at(j + 1));
            }
            else if ((i == (blocksWidth - 1)) && (j == (blocksHeight - 1))) {
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i - 1).at(j));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i -1).at(j - 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i).at(j - 1));
            }
            else if ((i == 0) && (j != 0 && j != (blocksHeight - 1))) {
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i).at(j - 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j - 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j + 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i).at(j + 1));
            }
            else if ((i != 0 && i != (blocksWidth - 1)) && (j == 0)) {
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i - 1).at(j));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i - 1).at(j + 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i).at(j + 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j + 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j));
            }
            else if ((i == (blocksWidth - 1)) && (j != 0 && j != (blocksHeight - 1))) {
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i).at(j - 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i - 1).at(j - 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i - 1).at(j));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i - 1).at(j + 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i).at(j + 1));
            }
            else if ((i != 0 && i != (blocksWidth - 1)) && (j == (blocksHeight - 1))) {
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i - 1).at(j));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i - 1).at(j - 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i).at(j - 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j - 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j));
            }
            else {
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i - 1).at(j));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i - 1).at(j - 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i).at(j - 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j - 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i + 1).at(j + 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i).at(j + 1));
                gameBoardVector.at(i).at(j).neighbors.push_back(&gameBoardVector.at(i - 1).at(j + 1));
            }            
        }
    }
    for (unsigned int i = 0; i < blocksWidth; i++) {
        for (unsigned int j = 0; j < blocksHeight; j++) {
            for (unsigned int k = 0; k < gameBoardVector.at(i).at(j).neighbors.size(); k++) {
                if (gameBoardVector.at(i).at(j).neighbors.at(k)->isBomb) {
                    gameBoardVector.at(i).at(j).neighboringBombs++;
                }
            }
            if (gameBoardVector.at(i).at(j).neighboringBombs != 0) {
                gameBoardVector.at(i).at(j).clickedTile.setTexture(TextureManager::GetTexture("number_" + to_string(gameBoardVector.at(i).at(j).neighboringBombs)));
            }
        }
    }
}

void Board::RecursiveReveal(Tile& tile, bool gameStatus) {
    if (!tile.isClicked && !tile.isFlag && gameStatus) {
        tile.isClicked = true;
        if (tile.neighboringBombs == 0) {
            for (unsigned int i = 0; i < tile.neighbors.size(); i++) {
                RecursiveReveal(*(tile.neighbors.at(i)), gameStatus);
            }
        }
    }
}

bool Board::GameWin(unsigned int mineCount, unsigned int blocksWidth, unsigned int blocksHeight) {
    int clickedCount = 0;
    for (unsigned int i = 0; i < blocksWidth; i++) {
        for (unsigned int j = 0; j < blocksHeight; j++) {
            if (gameBoardVector.at(i).at(j).isClicked == true) {
                clickedCount++;
                if (clickedCount == ((blocksWidth * blocksHeight) - mineCount)) {
                    return true;
                }
            }
        }
    }
    return false;
}