#include "Texture.h"

Texture::Texture(const char* path)
{
	mTexture.loadFromFile(path);
}
