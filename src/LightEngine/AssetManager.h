#pragma once
#include <map>

class Texture;
class Animation;

class AssetManager
{
	static AssetManager* instance;

	std::map<const char*, Texture*> mTextures;

private:
	Texture* LoadTexture(const char* path);

public:
	static AssetManager* Get();

	Texture* GetTexture(const char* path);
};

