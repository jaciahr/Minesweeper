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

void TestBoard(Board& board, string file, const unsigned int blocksWidth, const unsigned int blocksHeight, int& testboardBombs) {
    testboardBombs = 0;
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
                    testboardBombs++;
                }
            }
        }
        board.CalculateNeighbors(blocksWidth, blocksHeight);
        testboardData.close();
    }
}


int main()
{
    int testboardBombs = 0;
    unsigned int blocksWidth = 0;
    unsigned int blocksHeight = 0;
    unsigned int mineCount = 0;
    

    ConfigureBoard("config", blocksWidth, blocksHeight, mineCount);
    int mineCountWithFlags = mineCount;

    unsigned int windowWidth = blocksWidth * 32;
    unsigned int windowHeight = (blocksHeight * 32) + 88;

    // Magic stuff (background)
    sf::Texture backgroundText;
    backgroundText.setRepeated(true);
    backgroundText.loadFromFile("images/tile_revealed.png");
    sf::IntRect backgroundRect(0, 0, windowWidth, (windowHeight - 88));
    sf::Sprite background(backgroundText, backgroundRect);
    
    
    /*sf::Sprite digits[11];
    for (int i = 0; i < 11; i++) {
        string digit = "number" + to_string(i);
        
    }*/

    

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
    
    Board board = Board(mineCount, blocksWidth, blocksHeight);
    for (unsigned int i = 0; i < blocksWidth; i++) {
        for (unsigned int j = 0; j < blocksHeight; j++) {
            board.gameBoardVector.at(i).at(j).SetPosition(i * 32.0f, j * 32.0f);
        }
    }
    
    // Pick a board! Random, or one of the test boards?

    //TestBoard(board, "testboard3");
    sf::Sprite clickedTile2(TextureManager::GetTexture("tile_revealed"));
    sf::Sprite smiley(TextureManager::GetTexture("face_happy"));
    smiley.setPosition(sf::Vector2f((windowWidth / 2), (windowHeight - 88)));
    sf::Sprite sad(TextureManager::GetTexture("face_lose"));
    sad.setPosition(sf::Vector2f((windowWidth / 2), (windowHeight - 88)));
    sf::Sprite winner(TextureManager::GetTexture("face_win"));
    winner.setPosition(sf::Vector2f((windowWidth / 2), (windowHeight - 88)));
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
    bool gameStatus = true;

    //**************SPAMMING NUMBER SPRITES******************
    vector<sf::Sprite> digits;

    sf::Texture number0texture;
    number0texture.loadFromFile("images/digits.png");
    sf::IntRect number0rect(0, 0, 21, 32);
    sf::Sprite number0sprite(number0texture, number0rect);
    number0sprite.setPosition(0, (blocksHeight * 32));
    digits.push_back(number0sprite);

    sf::Texture number1texture;
    number1texture.loadFromFile("images/digits.png");
    sf::IntRect number1rect(21, 0, 21, 32);
    sf::Sprite number1sprite(number1texture, number1rect);
    digits.push_back(number1sprite);

    sf::Texture number2texture;
    number2texture.loadFromFile("images/digits.png");
    sf::IntRect number2rect(42, 0, 21, 32);
    sf::Sprite number2sprite(number2texture, number2rect);
    digits.push_back(number2sprite);

    sf::Texture number3texture;
    number3texture.loadFromFile("images/digits.png");
    sf::IntRect number3rect(63, 0, 21, 32);
    sf::Sprite number3sprite(number3texture, number3rect);
    digits.push_back(number3sprite);

    sf::Texture number4texture;
    number4texture.loadFromFile("images/digits.png");
    sf::IntRect number4rect(84, 0, 21, 32);
    sf::Sprite number4sprite(number4texture, number4rect);
    digits.push_back(number4sprite);

    sf::Texture number5texture;
    number5texture.loadFromFile("images/digits.png");
    sf::IntRect number5rect(105, 0, 21, 32);
    sf::Sprite number5sprite(number5texture, number5rect);
    digits.push_back(number5sprite);

    sf::Texture number6texture;
    number6texture.loadFromFile("images/digits.png");
    sf::IntRect number6rect(126, 0, 21, 32);
    sf::Sprite number6sprite(number6texture, number6rect);
    digits.push_back(number6sprite);

    sf::Texture number7texture;
    number7texture.loadFromFile("images/digits.png");
    sf::IntRect number7rect(147, 0, 21, 32);
    sf::Sprite number7sprite(number7texture, number7rect);
    digits.push_back(number7sprite);

    sf::Texture number8texture;
    number8texture.loadFromFile("images/digits.png");
    sf::IntRect number8rect(168, 0, 21, 32);
    sf::Sprite number8sprite(number8texture, number8rect);
    digits.push_back(number8sprite);

    sf::Texture number9texture;
    number9texture.loadFromFile("images/digits.png");
    sf::IntRect number9rect(189, 0, 21, 32);
    sf::Sprite number9sprite(number9texture, number9rect);
    digits.push_back(number9sprite);

    sf::Texture minustexture;
    minustexture.loadFromFile("images/digits.png");
    sf::IntRect minusrect(210, 0, 21, 32);
    sf::Sprite minussprite(minustexture, minusrect);

//************************************************************************
    

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
                                if (board.gameBoardVector.at(i).at(j).isBomb == true) {
                                    if (!board.gameBoardVector.at(i).at(j).isFlag && !(board.GameWin(mineCount, blocksWidth, blocksHeight))) {
                                        gameStatus = false;
                                        debugClicked = true;
                                    }
                                }
                                else if (board.gameBoardVector.at(i).at(j).isBomb == false) {
                                    board.RecursiveReveal(board.gameBoardVector.at(i).at(j), gameStatus);
                                }
                            }
                        }
                    }
                    if (debugSprite.getGlobalBounds().contains(position.x, position.y)) {
                        if (!gameStatus) {
                            debugClicked = false;
                        }
                        if (board.GameWin(mineCount, blocksWidth, blocksHeight)) {
                            debugClicked = false;
                        }
                        debugClicked = !debugClicked;
                    }
                    if (test1.getGlobalBounds().contains(position.x, position.y)) {
                        TestBoard(board, "testboard1", blocksWidth, blocksHeight, testboardBombs);
                        mineCountWithFlags = testboardBombs;
                        if (!gameStatus) {
                            gameStatus = true;
                            debugClicked = false;
                        }
                    }
                    if (test2.getGlobalBounds().contains(position.x, position.y)) {
                        TestBoard(board, "testboard2", blocksWidth, blocksHeight, testboardBombs);
                        mineCountWithFlags = testboardBombs;
                        if (!gameStatus) {
                            gameStatus = true;
                            debugClicked = false;
                        }
                    }
                    if (test3.getGlobalBounds().contains(position.x, position.y)) {
                        TestBoard(board, "testboard3", blocksWidth, blocksHeight, testboardBombs);
                        mineCountWithFlags = testboardBombs;
                        if (!gameStatus) {
                            gameStatus = true;
                            debugClicked = false;
                        }
                    }
                    if (smiley.getGlobalBounds().contains(position.x, position.y)) {
                        for (unsigned int i = 0; i < blocksWidth; i++) {
                            for (unsigned int j = 0; j < blocksHeight; j++) {
                                board.gameBoardVector.at(i).at(j).isBomb = false;
                            }
                        }
                        board.gameBoardVector.clear();
                        mineCountWithFlags = mineCount;
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
                    if (sad.getGlobalBounds().contains(position.x, position.y)) {
                        gameStatus = true;
                        debugClicked = false;
                    }
                    if (winner.getGlobalBounds().contains(position.x, position.y)) {
                        gameStatus = true;
                        debugClicked = false;
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2i position = sf::Mouse::getPosition(window);

                    for (unsigned int i = 0; i < blocksWidth; i++) {
                        for (unsigned int j = 0; j < blocksHeight; j++) {
                            if (board.gameBoardVector.at(i).at(j).GetSpriteRect().contains(position.x, position.y))
                            {
                                /*cout << board.GameWin(mineCount, blocksWidth, blocksHeight) << endl;
                                cout << gameStatus << endl;
                                cout << board.gameBoardVector.at(i).at(j).isClicked << endl;*/
                                bool haveWon = board.GameWin(mineCount, blocksWidth, blocksHeight);

                                if (gameStatus) {
                                    if (!board.gameBoardVector.at(i).at(j).isClicked) {
                                        board.gameBoardVector.at(i).at(j).isFlag = !board.gameBoardVector.at(i).at(j).isFlag;
                                        if (board.gameBoardVector.at(i).at(j).isFlag) {
                                            mineCountWithFlags--;
                                        }
                                        else {
                                            mineCountWithFlags++;
                                        }
                                    }
                                }
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
                if (board.gameBoardVector.at(i).at(j).isBomb && board.GameWin(mineCount, blocksWidth, blocksHeight)) {
                    window.draw(board.gameBoardVector.at(i).at(j).flag);
                }
                else if (board.gameBoardVector.at(i).at(j).isBomb && board.gameBoardVector.at(i).at(j).isClicked && !board.GameWin(mineCount, blocksWidth, blocksHeight)) {
                    if (board.gameBoardVector.at(i).at(j).isFlag) {
                        window.draw(board.gameBoardVector.at(i).at(j).flag);
                        window.draw(board.gameBoardVector.at(i).at(j).bomb);
                    }
                    else {
                        window.draw(board.gameBoardVector.at(i).at(j).clickedTile);
                        window.draw(board.gameBoardVector.at(i).at(j).bomb);
                    }
                }
            }
        }

        //   Bombs (debug mode)
        for (unsigned int i = 0; i < blocksWidth; i++) {
            for (unsigned int j = 0; j < blocksHeight; j++) {
                if (board.gameBoardVector.at(i).at(j).isBomb && debugClicked && !board.GameWin(mineCount, blocksWidth, blocksHeight)) {
                    if (gameStatus) {
                        window.draw(board.gameBoardVector.at(i).at(j).bomb);
                    }
                    else if (board.gameBoardVector.at(i).at(j).isFlag) {
                        window.draw(board.gameBoardVector.at(i).at(j).flag);
                        window.draw(board.gameBoardVector.at(i).at(j).bomb);
                    }
                    else {
                        window.draw(board.gameBoardVector.at(i).at(j).clickedTile);
                        window.draw(board.gameBoardVector.at(i).at(j).bomb);
                    }
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
        
        int onesInt = mineCountWithFlags % 10;
        int tensInt = (mineCountWithFlags / 10) % 10;
        int hundredthsInt = mineCountWithFlags / 100;

        if (mineCountWithFlags < 0) {
            minussprite.setPosition(0, (blocksHeight * 32));
            window.draw(minussprite);
        }
        if (onesInt < 0) {
            onesInt *= -1;
        }
        if (tensInt < 0) {
            tensInt *= -1;
        }
        if (onesInt < 0) {
            hundredthsInt *= -1;
        }
        if (board.GameWin(mineCount, blocksWidth, blocksHeight)) {
            onesInt = 0;
            tensInt = 0;
            hundredthsInt = 0;
        }

        digits[onesInt].setPosition(63, (blocksHeight * 32));
        window.draw(digits[onesInt]);

        digits[tensInt].setPosition(42, (blocksHeight * 32));
        window.draw(digits[tensInt]);

        digits[hundredthsInt].setPosition(21, (blocksHeight * 32));
        window.draw(digits[hundredthsInt]);
        

        if (!gameStatus) {
            window.draw(sad);
        }
        if (board.GameWin(mineCount, blocksWidth, blocksHeight)) {
            window.draw(winner);
        }
        //3. Display all the stuff you drew
        window.display();
    }

    TextureManager::Clear();
    
    return 0;
}
    
