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
	m_window.setActive(false);

	std::thread renderThread(&Game::render, std::ref(*this));

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

		/*	if (event.type == sf::Event::Resized)
			{
				m_window.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
			}*/
		}
	}

	renderThread.join();
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
	// TODO: Find some way to be able to make a loading screen in derived class
	// instead of here...
	sf::Text loadingText;
	loadingText.setFont(m_fontMan.get("./Roboto-Regular.ttf"));
	loadingText.setString("Loading Grid...");
	loadingText.setCharacterSize(69);
	loadingText.setFillColor(sf::Color::White);
	loadingText.setStyle(sf::Text::Bold);

	bool bDoneLoading = false;

	std::thread initThread([&bDoneLoading, this]() {
		onGameStart();
		bDoneLoading = true;
	});
	

	sf::Clock clock;

	while (m_window.isOpen())
	{
		m_window.clear();

		float elapsedTime = clock.restart().asSeconds();

		if (m_bShowFPS)
		{
			m_window.setTitle(m_name + " - FPS: " + std::to_string(1 / elapsedTime));
		}

		if (bDoneLoading == false)
		{
			m_window.draw(loadingText);
		}
		else
		{
			update(elapsedTime);

			for (size_t i = 0; i < m_drawables.size(); i++)
			{
				if (m_drawables[i] != nullptr)
				{
					m_window.draw(*(m_drawables[i]));
				}
			}
		}

		m_window.display();
	}

	initThread.join();
	
}
