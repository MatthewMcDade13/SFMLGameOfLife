#include "stdafx.h"
#include "Game.h"
#include "Grid.h"
#include "Cell.h"

#include <thread>
#include <exception>

using sf::VideoMode;
using sf::RenderWindow;

Game::Game()
{
}

Game::~Game()
{
}

RenderWindow& Game::getWindow()
{
	return m_window;
}

void Game::createWindow(const VideoMode vm, const std::string& title)
{
	m_name = title;
	m_window.create(vm, title);
}

void Game::start()
{
	onGameStart();

	sf::Clock clock;

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}

			handleInput(event);
		}

		m_window.clear();

		float elapsedTime = clock.restart().asSeconds();

		if (m_bShowFPS)
		{
			m_window.setTitle(m_name + " - FPS: " + std::to_string(1 / elapsedTime));
		}

		update(elapsedTime);

		for (size_t i = 0; i < m_drawables.size(); i++)
		{
			if (m_drawables[i] != nullptr)
			{
				m_window.draw(*(m_drawables[i]));
			}
		}


		m_window.display();
	}

}

void Game::setFPS(bool show)
{
	m_bShowFPS = show;
}

void Game::addDrawable(sf::Drawable* drawable)
{
	m_drawables.push_back(drawable);
}

void Game::render()
{

	
}
