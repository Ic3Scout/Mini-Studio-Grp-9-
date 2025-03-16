#include "AssetManager.h"
#include <iostream>

AssetManager* AssetManager::instance = nullptr;

sf::Texture* AssetManager::LoadTexture(const char* path)
{
    sf::Texture* pTexture = new sf::Texture();

    if (!pTexture->loadFromFile(path))
    {
        std::cerr << "Chargement texture mal";
    }

    mTextures[path] = pTexture;

    return pTexture;
}

AssetManager* AssetManager::Get()
{
    if (instance == nullptr)
    {
        instance = new AssetManager();
    }

    return instance;
}

sf::Texture* AssetManager::GetTexture(const char* path)
{
    auto it = mTextures.find(path);

    if (it == mTextures.end())
    {
        return LoadTexture(path);
    }

    return it->second;
}
