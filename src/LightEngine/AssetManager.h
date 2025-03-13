#pragma once
#include <map>

class Texture;

class AssetManager
{
	std::map<const char*, Texture*> mTextures;

private:
	Texture* LoadTexture(const char* path);

public:
	Texture* GetTexture(const char* path);
};

