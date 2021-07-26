#include "Tile.h"
#include "TextureManager.h"
Tile::Tile() {
    unclickedTile.setTexture(TextureManager::GetTexture("tile_hidden"));
    clickedTile.setTexture(TextureManager::GetTexture("tile_revealed"));
    flag.setTexture(TextureManager::GetTexture("flag"));
    bomb.setTexture(TextureManager::GetTexture("mine"));
    isClicked = false;
    isFlag = false;
    isBomb = false;
    neighboringBombs = 0;
}

Tile::Tile(bool isClicked, bool isFlag, bool isBomb, unsigned int neighboringBombs) {
    this->isClicked = isClicked;
    this->isFlag = isFlag;
    this->isBomb = isBomb;
    this->neighboringBombs;
    unclickedTile.setTexture(TextureManager::GetTexture("tile_hidden"));
    clickedTile.setTexture(TextureManager::GetTexture("tile_revealed"));
    flag.setTexture(TextureManager::GetTexture("flag"));
    bomb.setTexture(TextureManager::GetTexture("mine"));
}

void Tile::SetPosition(float x, float y) {
    clickedTile.setPosition(x, y);
    unclickedTile.setPosition(x, y);
    flag.setPosition(x, y);
    bomb.setPosition(x, y);
}

void Tile::SetPosition(sf::Vector2f position) {
    clickedTile.setPosition(position);
    unclickedTile.setPosition(position);
    flag.setPosition(position);
    bomb.setPosition(position);
}

sf::FloatRect Tile::GetSpriteRect() {
    if (isClicked)
        return unclickedTile.getGlobalBounds();
    else
        return clickedTile.getGlobalBounds();
}