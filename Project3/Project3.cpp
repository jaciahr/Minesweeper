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

        

        //sf::CircleShape shape(50.f);
        //shape.setFillColor(sf::Color::Cyan);
        //shape.setPosition(400, 200);

        //Tile someTile;
        //someTile.SetPosition(300, 0);

        sf::Sprite debugSprite(TextureManager::GetTexture("debug"));
        debugSprite.setPosition((windowWidth / 2), windowHeight);
        ////Random randObject;
        ////int value = Random::x; //doing the same thing as...
        ////value = randObject.x; //... this

        //int randomX = Random::Int(0, window.getSize().x);
        //cout << randomX;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                /*else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i position = sf::Mouse::getPosition(window);

                        if (someTile.GetSpriteRect().contains(position.x, position.y))
                        {
                            someTile.isClicked = !someTile.isClicked;
                        }
                    }
                }*/
            }

            //1. Erase everything previously drawn
            window.clear(sf::Color::White);

            //2. Draw stuff you want to appear on the screen
            /*sf::Sprite debugSprite(TextureManager::GetTexture("debug"));
                window.draw(debugSprite);*/

            for (unsigned int i = 0; i < blocksWidth; i++) {
                for (unsigned int j = 0; j < blocksHeight; j++) {
                    window.draw(board.gameBoardVector.at(i).at(j).unclickedTile);
                }
            }

            
            /*Tile someTile;
            window.draw(someTile.clickedTile);*/

            /*for (int i = 0; i < 10; i++) {
                shape.setPosition(shape.getRadius() * 2 * i, 0);
                window.draw(shape);
            }*/

            window.draw(debugSprite);
            /*for (int i = 0; i < 2; i++) {
                if (someTile.isClicked)
                    window.draw(someTile.clickedTile);
                else
                    window.draw(someTile.unclickedTile);
            }*/
            //3. Display all the stuff you drew
            window.display();
        }

        TextureManager::Clear();
        boardConfig.close();
    }
    return 0;
}