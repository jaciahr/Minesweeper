#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

class Tile {
    
public:
    bool isClicked;
    bool isFlag;
    bool isBomb;
    unsigned int neighboringBombs = 0;
    sf::Sprite unclickedTile;
    sf::Sprite clickedTile;
    sf::Sprite flag;
    sf::Sprite bomb;
    sf::Sprite number1;
    vector <Tile*> neighbors;
    
    void SetPosition(float x, float y);
    void SetPosition(sf::Vector2f position);

    Tile();
    Tile(bool isClicked, bool isFlag, bool isBomb, unsigned int neighboringBombs, vector <Tile*> neighbors);

    bool GetIsClicked() {
        return isClicked;
    }

    bool GetIsFlag() {
        return isFlag;
    }

    bool GetIsBomb() {
        return isBomb;
    }

    unsigned int GetNeighboringBombs() {
        return neighboringBombs;
    }

    void SetIsClicked(bool isClicked) {
        this->isClicked = isClicked;
    }

    sf::FloatRect GetSpriteRect();
};