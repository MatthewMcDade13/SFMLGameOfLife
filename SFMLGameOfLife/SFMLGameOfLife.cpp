// SFMLGameOfLife.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "GameOfLife.h"

int main()
{
	GameOfLife game;
	game.createWindow(sf::VideoMode(1000, 1000), "Game Of Life");
	game.setFPS(true);
	game.start();

	return 0;
}



