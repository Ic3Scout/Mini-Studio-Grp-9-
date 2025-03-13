#include "AssetManager.h"
#include "Texture.h"

Texture* AssetManager::LoadTexture(const char* path)
{
    Texture* pTexture = new Texture(path);
    mTextures[path] = pTexture;

    return pTexture;
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
