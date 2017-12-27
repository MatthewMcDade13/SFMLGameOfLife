#pragma once

#include "ResourceManager.h"

namespace sf
{
	class Texture;
	class Font;
	class Image;
}

struct ResourceHolder
{
	ResourceManager<sf::Texture> textureManager;
	ResourceManager<sf::Font> fontManager;
	ResourceManager<sf::Image> imageManager;
};