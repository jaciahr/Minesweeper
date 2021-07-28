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

void TestBoard(Board& board, string file, const unsigned int blocksWidth, const unsigned int blocksHeight) {
    char testboardInput;
    ifstream testboardData;
    string line;
    string filename = "boards/" + file + ".brd";
    testboardData.open(filename);
    if (testboardData.is_open()) {
        board.gameBoardVector.clear();
        for (unsigned int i = 0; i < blocksWidth; i++) {
            for (unsigned int j = 0; j < blocksHeight; j++) {
                Tile newTile;
                board.gameBoardSubVector.push_back(newTile);
            }
            board.gameBoardVector.push_back(board.gameBoardSubVector);
            board.gameBoardSubVector.clear();
        }
        for (unsigned int i = 0; i < blocksWidth; i++) {
            for (unsigned int j = 0; j < blocksHeight; j++) {
                board.gameBoardVector.at(i).at(j).SetPosition(i * 32.0f, j * 32.0f);
            }
        }
        for (int i = 0; i < blocksHeight; i++) {
            testboardData >> line;
            for (int j = 0; j < blocksWidth; j++) {
                board.gameBoardVector.at(j).at(i).isBomb = false;
                testboardInput = line.at(j);
                if (testboardInput == '1') {
                    board.gameBoardVector.at(j).at(i).isBomb = true;
                }
            }
        }
        board.CalculateNeighbors(blocksWidth, blocksHeight);
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

    // Magic stuff (background)
    sf::Texture backgroundText;
    backgroundText.setRepeated(true);
    backgroundText.loadFromFile("images/tile_revealed.png");
    sf::IntRect backgroundRect(0, 0, windowWidth, (windowHeight - 88));
    sf::Sprite background(backgroundText, backgroundRect);
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
    
    Board board = Board(mineCount, blocksWidth, blocksHeight);
    for (unsigned int i = 0; i < blocksWidth; i++) {
        for (unsigned int j = 0; j < blocksHeight; j++) {
            board.gameBoardVector.at(i).at(j).SetPosition(i * 32.0f, j * 32.0f);
        }
    }
    
    // Pick a board! Random, or one of the test boards?

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

    

    // Numbers
    /*for (unsigned int i = 0; i < blocksWidth; i++) {
        for (unsigned int j = 0; j < blocksHeight; j++) {
            if (board.gameBoardVector.at(i).at(j).neighboringBombs == 1)
                number1.setPosition(sf::Vector2f(i, j));
        }
    }*/

    sf::Sprite number2(TextureManager::GetTexture("number_2"));
    sf::Sprite number3(TextureManager::GetTexture("number_3"));
    sf::Sprite number4(TextureManager::GetTexture("number_4"));
    sf::Sprite number5(TextureManager::GetTexture("number_5"));
    sf::Sprite number6(TextureManager::GetTexture("number_6"));
    sf::Sprite number7(TextureManager::GetTexture("number_7"));
    sf::Sprite number8(TextureManager::GetTexture("number_8"));

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
                        TestBoard(board, "testboard1", blocksWidth, blocksHeight);
                    }
                    if (test2.getGlobalBounds().contains(position.x, position.y)) {
                        TestBoard(board, "testboard2", blocksWidth, blocksHeight);
                    }
                    if (test3.getGlobalBounds().contains(position.x, position.y)) {
                        TestBoard(board, "testboard3", blocksWidth, blocksHeight);
                    }
                    if (smiley.getGlobalBounds().contains(position.x, position.y)) {
                        for (unsigned int i = 0; i < blocksWidth; i++) {
                            for (unsigned int j = 0; j < blocksHeight; j++) {
                                board.gameBoardVector.at(i).at(j).isBomb = false;
                            }
                        }
                        board.gameBoardVector.clear();
                        for (unsigned int i = 0; i < blocksWidth; i++) {
                            for (unsigned int j = 0; j < blocksHeight; j++) {
                                Tile newTile;
                                board.gameBoardSubVector.push_back(newTile);
                            }
                            board.gameBoardVector.push_back(board.gameBoardSubVector);
                            board.gameBoardSubVector.clear();
                        }
                        for (unsigned int i = 0; i < blocksWidth; i++) {
                            for (unsigned int j = 0; j < blocksHeight; j++) {
                                board.gameBoardVector.at(i).at(j).SetPosition(i * 32.0f, j * 32.0f);
                            }
                        }
                        board.MineTime(mineCount, blocksWidth, blocksHeight);
                        board.CalculateNeighbors(blocksWidth, blocksHeight);
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
        
        window.draw(background);

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
        //********* Put into one nested for loop pls!

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

        // Numbers...?
        /*for (unsigned int i = 0; i < blocksWidth; i++) {
            for (unsigned int j = 0; j < blocksHeight; j++) {
                if ((board.gameBoardVector.at(i).at(j).neighboringBombs == 1) && (board.gameBoardVector.at(i).at(j).isClicked)) {
                    window.draw(board.gameBoardVector.at(i).at(j).number1);
                }
            }
        }*/

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
    
