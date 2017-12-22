// SFMLGameOfLife.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "GameOfLife.h"
#include "GetConsoleInput.h"

int main()
{
	using namespace std;

	GameOfLife game;
	game.setGameSettings();
	game.createWindow(sf::VideoMode(1920, 1080), "Game Of Life");
	game.setFPS(true);	
	game.start();

	return 0;
}



