#include "stdafx.h"
#include "Game.h"
#include "Grid.h"
#include "Cell.h"
#include "ResourceHolder.h"

#include <thread>
#include <exception>

using sf::VideoMode;
using sf::RenderWindow;

Game::Game() : m_context({ &m_resources }), m_resources()
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
	m_context.window = &m_window;
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

		m_window.display();
	}

}

void Game::setFPS(bool show)
{
	m_bShowFPS = show;
}

