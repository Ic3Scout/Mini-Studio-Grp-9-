#pragma once
#include <map>
#include <SFML/Graphics/Texture.hpp>

class AssetManager
{
	static AssetManager* instance;

	std::map<const char*, sf::Texture*> mTextures;

private:
	sf::Texture* LoadTexture(const char* path);

public:
	static AssetManager* Get();

	sf::Texture* GetTexture(const char* path);
};

