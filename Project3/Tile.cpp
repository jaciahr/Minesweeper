#include "Tile.h"
#include "TextureManager.h"
Tile::Tile() {
    unclickedTile.setTexture(TextureManager::GetTexture("tile_hidden"));
    clickedTile.setTexture(TextureManager::GetTexture("tile_revealed"));
    flag.setTexture(TextureManager::GetTexture("flag"));
    bomb.setTexture(TextureManager::GetTexture("mine"));
    number1.setTexture(TextureManager::GetTexture("number_1"));
    isClicked = false;
    isFlag = false;
    isBomb = false;
    neighboringBombs = 0;
}

Tile::Tile(bool isClicked, bool isFlag, bool isBomb, unsigned int neighboringBombs, vector <Tile*> neighbors) {
    this->isClicked = isClicked;
    this->isFlag = isFlag;
    this->isBomb = isBomb;
    this->neighboringBombs = neighboringBombs;
    unclickedTile.setTexture(TextureManager::GetTexture("tile_hidden"));
    clickedTile.setTexture(TextureManager::GetTexture("tile_revealed"));
    flag.setTexture(TextureManager::GetTexture("flag"));
    bomb.setTexture(TextureManager::GetTexture("mine"));
    number1.setTexture(TextureManager::GetTexture("number_1"));
}

void Tile::SetPosition(float x, float y) {
    clickedTile.setPosition(x, y);
    unclickedTile.setPosition(x, y);
    flag.setPosition(x, y);
    bomb.setPosition(x, y);
    number1.setPosition(x, y);
}

void Tile::SetPosition(sf::Vector2f position) {
    clickedTile.setPosition(position);
    unclickedTile.setPosition(position);
    flag.setPosition(position);
    bomb.setPosition(position);
    number1.setPosition(position);
}

sf::FloatRect Tile::GetSpriteRect() {
    if (isClicked)
        return unclickedTile.getGlobalBounds();
    else
        return clickedTile.getGlobalBounds();
}