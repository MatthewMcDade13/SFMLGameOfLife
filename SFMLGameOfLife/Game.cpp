#include "stdafx.h"
#include "Game.h"
#include "Grid.h"
#include "Cell.h"
#include "ResourceHolder.h"

#include <thread>
#include <exception>

using sf::VideoMode;
using sf::RenderWindow;

Game::Game() : 
	m_context({ &m_resources }), 
	m_resources(),
	m_bShowFPS(false),
	m_bUseFixedTimeStep(true),
	m_timePerFrame(sf::seconds(1.f / 120.f))
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
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		processInput();

		if (m_bUseFixedTimeStep)
		{
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate >= m_timePerFrame)
			{
				timeSinceLastUpdate -= m_timePerFrame;
				processInput();
				update(m_timePerFrame.asSeconds());
			}

			render();
		}
		else
		{
			timeSinceLastUpdate = clock.restart();
			update(timeSinceLastUpdate.asSeconds());
			render();
		}

		if (m_bShowFPS)
		{
			m_window.setTitle(m_name + " - FPS: " + std::to_string(1 / timeSinceLastUpdate.asSeconds()));
		}

	}

}

void Game::setFPS(bool show)
{
	m_bShowFPS = show;
}

void Game::setFrameTime(float framesPerSecond)
{
	m_timePerFrame = sf::seconds(1.f / framesPerSecond);
}

void Game::setUseFixedTimeStep(bool shouldUseTimeStep)
{
	m_bUseFixedTimeStep = shouldUseTimeStep;
}

void Game::processInput()
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
}

void Game::render()
{
	m_window.clear();
	draw();
	m_window.display();
}

