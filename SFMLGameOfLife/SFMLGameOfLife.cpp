// SFMLGameOfLife.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "GameOfLife.h"
#include "GetConsoleInput.h"
#include "Grid.h"

int main()
{
	GameOfLife game;
	game.createWindow(sf::VideoMode(1920, 1080), "Game Of Life");
	game.setFPS(true);
	//game.setUseFixedTimeStep(false);
	game.start();

	return EXIT_SUCCESS;
}



