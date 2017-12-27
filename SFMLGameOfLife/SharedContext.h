#pragma once

namespace sf
{
	class RenderWindow;
}

#include "ResourceHolder.h"

struct SharedContext
{
	ResourceHolder* resources;
	sf::RenderWindow* window;
};