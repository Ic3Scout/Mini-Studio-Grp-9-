#include "AssetManager.h"
#include "Texture.h"

AssetManager* AssetManager::instance = nullptr;

Texture* AssetManager::LoadTexture(const char* path)
{
    Texture* pTexture = new Texture(path);
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

Texture* AssetManager::GetTexture(const char* path)
{
    auto it = mTextures.find(path);

    if (it == mTextures.end())
    {
        return LoadTexture(path);
    }

    return it->second;
}
