#pragma once
#include <SFML/Graphics/Texture.hpp>

class Texture
{
	sf::Texture mTexture;

public:
	Texture(const char* path);
};

