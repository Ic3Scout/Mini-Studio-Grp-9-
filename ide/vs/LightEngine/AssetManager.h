#pragma once
#include <map>
#include <SFML/Graphics.hpp>

class AssetManager
{
	std::map<const char*, sf::Texture*> mTextures;

private:
	sf::Texture* LoadTexture(const char* path);

	sf::Texture* GetTexture(const char* path);
};

