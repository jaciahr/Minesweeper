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

int main()
{
    ifstream boardConfig;
    boardConfig.open("boards/config.cfg");
    string line;
    unsigned int blocksWidth = 0;
    unsigned int blocksHeight = 0;
    unsigned int mineCount = 0;

    if (boardConfig.is_open()) {
        stringstream parse(line);
        boardConfig >> blocksWidth;
        boardConfig >> blocksHeight;
        boardConfig >> mineCount;

        unsigned int windowWidth = blocksWidth * 32;
        unsigned int windowHeight = (blocksHeight * 32) + 88;

        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
        
        Board board = Board(blocksWidth, blocksHeight);
        for (unsigned int i = 0; i < blocksWidth; i++) {
            for (unsigned int j = 0; j < blocksHeight; j++) {
                board.gameBoardVector.at(i).at(j).SetPosition(i * 32.0f, j * 32.0f);
            }
        }

        //Tile someTile;
        //someTile.SetPosition(300, 0);
        
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

        /*sf::Texture texture;
        if (!texture.loadFromFile("images/debug.png"))
        {
            cout << "Error";
        }
        sf::Sprite sprite;
        sprite.setTexture("images/debug.png");
        sprite.setPosition(400.0f, 600.0f);*/

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
            /*sf::Texture texture = TextureManager::GetTexture("debug");
            sf::Sprite debugSprite(texture);
            debugSprite.setPosition((windowWidth / 2) - 60, windowHeight);*/
            
            //1. Erase everything previously drawn
            window.clear(sf::Color::White);

            //2. Draw stuff you want to appear on the screen

            for (unsigned int i = 0; i < blocksWidth; i++) {
                for (unsigned int j = 0; j < blocksHeight; j++) {
                    if (!board.gameBoardVector.at(i).at(j).isClicked)
                        window.draw(board.gameBoardVector.at(i).at(j).unclickedTile);
                    else
                        window.draw(board.gameBoardVector.at(i).at(j).clickedTile);
                }
            }

            for (unsigned int i = 0; i < blocksWidth; i++) {
                for (unsigned int j = 0; j < blocksHeight; j++) {
                    if (board.gameBoardVector.at(i).at(j).isFlag) {
                        window.draw(board.gameBoardVector.at(i).at(j).flag);
                        
                    }
                }
            }

            window.draw(debugSprite);
            window.draw(smiley);
            window.draw(test1);
            window.draw(test2);
            window.draw(test3);

            /*sf::Sprite debugSprite(TextureManager::GetTexture("debug"));
            debugSprite.setPosition(sf::Vector2f((windowWidth / 2) - 60, windowHeight));
            window.draw(debugSprite);*/
            /*window.draw(smiley);
            window.draw(test1);
            window.draw(test2);
            window.draw(test3);*/

            //3. Display all the stuff you drew
            window.display();
        }

        TextureManager::Clear();
        boardConfig.close();
    }

    /*bool bombPresent;
    ifstream testboard1;
    testboard1.open("boards/testboard1.brd");
    if (testboard1.is_open()) {
        while (getline (testboard1, line)) {
            stringstream parse(line);
            getline(parse, line);
            for (int i = 0; i < 25; i++) {
                board.gameBoardVector.at(i).at(j).isBomb = bool(line[i]);
            }
        }
    }*/

    return 0;
}