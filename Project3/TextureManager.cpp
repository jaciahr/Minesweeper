#include "TextureManager.h"

//declare the static variable (REQ.)
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(const char* fileName)
{
    string path = "images/";
    path += fileName;
    path += ".png";

    textures[fileName].loadFromFile(path);

    //ex. fileName == space
    //    path == images/space.png
}

sf::Texture& TextureManager::GetTexture(const char* textureName)
{
    //if the texture doesn't exist...
    if (textures.find(textureName) == textures.end()) //we didn't find it
    {
        LoadTexture(textureName); //load it first...
    }
    //...then return it
    return textures[textureName];
}

void TextureManager::Clear()
{
    textures.clear(); //get rid of all stored objects
}

//#include "TextureManager.h"
////declare the static variable (REQ.)
//unordered_map<string, sf::Texture> TextureManager::textures;
//
//void TextureManager::LoadTexture(string fileName)
//{
//    string path = "images/";
//    path += fileName + ".png";
//
//    textures[fileName].loadFromFile(path);
//
//    //ex. fileName == space
//    //    path == images/space.png
//}
//
//sf::Texture& TextureManager::GetTexture(string textureName)
//{
//    //if the texture doesn't exist...
//    if (textures.find(textureName) == textures.end()) //we didn't find it
//        LoadTexture(textureName); //load it first...
//
//    //...then return it
//    return textures[textureName];
//}
//
//void TextureManager::Clear()
//{
//    textures.clear(); //get rid of all stored objects
//}