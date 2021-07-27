#include <SFML/Graphics.hpp>
#include "Random.h"
#include <iostream>
#include "TextureManager.h"
#include "Tile.h"
#include "Board.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//vector<vector<char>> MineData(int boardWidth, int boardHeight, int mineCount) {
//    vector<vector<char>> mineDataVector;
//    int randomValue;
//    int count = 0;
//
//    for (int i = 0; i < boardWidth; i++) {
//        for (int j = 0; j < boardHeight; j++) {
//            randomValue = Random::Int(0, 999);
//            while (count < mineCount) {
//                if (randomValue % 10 == 0) {
//                    mineDataVector[i].push_back(1);
//                    count++;
//                }
//                else {
//                    mineDataVector[i].push_back(0);
//                }
//            }
//            cout << mineDataVector.at(i).at(j);
//        }
//    }
//    return mineDataVector;
//}

void MineTime(Board& board, unsigned int& mineCount, unsigned int& blocksWidth, unsigned int& blocksHeight) {
    unsigned int count = 0;
    unsigned int randomVal1;
    unsigned int randomVal2;
    while (count < mineCount) {
        randomVal1 = Random::Int(0, blocksWidth - 1);
        randomVal2 = Random::Int(0, blocksHeight - 1);
        if (board.gameBoardVector.at(randomVal1).at(randomVal2).isBomb == false) {
            board.gameBoardVector.at(randomVal1).at(randomVal2).isBomb = true;
            count++;
        }
    }
}

void ConfigureBoard(string file, unsigned int& blocksWidth, unsigned int& blocksHeight, unsigned int& mineCount) {
    ifstream boardConfig;
    string filename = "boards/" + file + ".cfg";
    boardConfig.open(filename);
    string line;

    if (boardConfig.is_open()) {
        stringstream parse(line);
        boardConfig >> blocksWidth;
        boardConfig >> blocksHeight;
        boardConfig >> mineCount;

        boardConfig.close();
    }
}

void TestBoard(Board& board, string file) {
    char testboardArray[16][25];
    ifstream testboardData;
    string line;
    string filename = "boards/" + file + ".brd";
    testboardData.open(filename);
    if (testboardData.is_open()) {
        for (int i = 0; i < 16; i++) {
            testboardData >> line;
            for (int j = 0; j < 25; j++) {
                board.gameBoardVector.at(j).at(i).isBomb = false;
                testboardArray[i][j] = line.at(j);
                if (testboardArray[i][j] == '1') {
                    board.gameBoardVector.at(j).at(i).isBomb = true;
                }
                cout << testboardArray[i][j];
            }
            cout << endl;
        }
        testboardData.close();
    }
}

int main()
{
    unsigned int blocksWidth = 0;
    unsigned int blocksHeight = 0;
    unsigned int mineCount = 0;

    ConfigureBoard("config", blocksWidth, blocksHeight, mineCount);

    unsigned int windowWidth = blocksWidth * 32;
    unsigned int windowHeight = (blocksHeight * 32) + 88;
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
    
    Board board = Board(blocksWidth, blocksHeight);
    for (unsigned int i = 0; i < blocksWidth; i++) {
        for (unsigned int j = 0; j < blocksHeight; j++) {
            board.gameBoardVector.at(i).at(j).SetPosition(i * 32.0f, j * 32.0f);
        }
    }
    
    // Pick a board! Random, or one of the test boards?

    MineTime(board, mineCount, blocksWidth, blocksHeight);
    //TestBoard(board, "testboard3");

    sf::Sprite smiley(TextureManager::GetTexture("face_happy"));
    smiley.setPosition(sf::Vector2f((windowWidth / 2), (windowHeight - 88)));
    sf::Sprite debugSprite(TextureManager::GetTexture("debug"));
    debugSprite.setPosition(sf::Vector2f((windowWidth - 240), (windowHeight - 88)));
    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    test1.setPosition(sf::Vector2f((windowWidth - 180), (windowHeight - 88)));
    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    test2.setPosition(sf::Vector2f((windowWidth - 120), (windowHeight - 88)));
    sf::Sprite test3(TextureManager::GetTexture("test_3"));
    test3.setPosition(sf::Vector2f((windowWidth - 60), (windowHeight - 88)));

    bool debugClicked = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i position = sf::Mouse::getPosition(window);

                    for (unsigned int i = 0; i < blocksWidth; i++) {
                        for (unsigned int j = 0; j < blocksHeight; j++) {
                            if (board.gameBoardVector.at(i).at(j).GetSpriteRect().contains(position.x, position.y))
                            {
                                board.gameBoardVector.at(i).at(j).isClicked = true;
                            }
                        }
                    }
                    if (debugSprite.getGlobalBounds().contains(position.x, position.y)) {
                        debugClicked = !debugClicked;
                    }
                    if (test1.getGlobalBounds().contains(position.x, position.y)) {
                        TestBoard(board, "testboard1");
                    }
                    if (test2.getGlobalBounds().contains(position.x, position.y)) {
                        TestBoard(board, "testboard2");
                    }
                    if (test3.getGlobalBounds().contains(position.x, position.y)) {
                        TestBoard(board, "testboard3");
                    }
                    if (smiley.getGlobalBounds().contains(position.x, position.y)) {
                        for (unsigned int i = 0; i < blocksWidth; i++) {
                            for (unsigned int j = 0; j < blocksHeight; j++) {
                                board.gameBoardVector.at(i).at(j).isBomb = false;
                            }
                        }
                        MineTime(board, mineCount, blocksWidth, blocksHeight);
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2i position = sf::Mouse::getPosition(window);

                    for (unsigned int i = 0; i < blocksWidth; i++) {
                        for (unsigned int j = 0; j < blocksHeight; j++) {
                            if (board.gameBoardVector.at(i).at(j).GetSpriteRect().contains(position.x, position.y))
                            {
                                if (!board.gameBoardVector.at(i).at(j).isClicked)
                                    board.gameBoardVector.at(i).at(j).isFlag = !board.gameBoardVector.at(i).at(j).isFlag;
                            }
                        }
                    }
                }
            }
        }
        
        //1. Erase everything previously drawn
        window.clear(sf::Color::White);

        //2. Draw stuff you want to appear on the screen
        //   Tiles
        for (unsigned int i = 0; i < blocksWidth; i++) {
            for (unsigned int j = 0; j < blocksHeight; j++) {
                if (!board.gameBoardVector.at(i).at(j).isClicked)
                    window.draw(board.gameBoardVector.at(i).at(j).unclickedTile);
                else
                    window.draw(board.gameBoardVector.at(i).at(j).clickedTile);
            }
        }
        //   Flags
        for (unsigned int i = 0; i < blocksWidth; i++) {
            for (unsigned int j = 0; j < blocksHeight; j++) {
                if (board.gameBoardVector.at(i).at(j).isFlag) {
                    window.draw(board.gameBoardVector.at(i).at(j).flag);
                    
                }
            }
        }

        //   Bombs (normal)
        for (unsigned int i = 0; i < blocksWidth; i++) {
            for (unsigned int j = 0; j < blocksHeight; j++) {
                if (board.gameBoardVector.at(i).at(j).isBomb && board.gameBoardVector.at(i).at(j).isClicked) {
                    window.draw(board.gameBoardVector.at(i).at(j).bomb);
                }
            }
        }

        //   Bombs (debug mode)
        for (unsigned int i = 0; i < blocksWidth; i++) {
            for (unsigned int j = 0; j < blocksHeight; j++) {
                if (board.gameBoardVector.at(i).at(j).isBomb && debugClicked) {
                    window.draw(board.gameBoardVector.at(i).at(j).bomb);
                }
            }
        }

        window.draw(debugSprite);
        window.draw(smiley);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);

        //3. Display all the stuff you drew
        window.display();
    }

    TextureManager::Clear();
    
    return 0;
}
    
