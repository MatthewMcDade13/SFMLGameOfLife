#pragma once

#include "ResourceHolder.h"
#include "Player.h"

namespace sf
{
	class RenderWindow;
}

struct Context
{
	ResourceHolder* resources;
	sf::RenderWindow* window;
	Player* player;
};