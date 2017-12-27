#include "stdafx.h"
#include "GameOfLife.h"
#include "Grid.h"
#include "Cell.h"
#include "CellState.h"
#include "GameSpeed.h"
#include "ResourceManager.h"
#include "parallelFor.h"
#include "GetConsoleInput.h"
#include "SplashScreen.h"
#include "GameState.h"
#include "Playing.h"
#include <memory>

using namespace std;

GameOfLife::GameOfLife() 
	: m_genDelay(0.1f), m_gameSpeed(GameSpeed::Fast), 
	m_bAddCells(true), m_grid(nullptr),
	m_stateManager(&m_context)
{
}


GameOfLife::~GameOfLife()
{
}

void GameOfLife::onGameStart()
{
	m_stateManager.registerState<SplashScreen>(static_cast<int>(GameState::Intro));
	m_stateManager.registerState<Playing>(static_cast<int>(GameState::Playing));

	m_stateManager.pushState(static_cast<int>(GameState::Intro));

	if (m_grid == nullptr)
	{
		m_grid = make_unique<Grid>(1000, 1000, 8);
		cout << "User settings not defined, resolving to default settings" << endl;
	}
}

void GameOfLife::update(float deltaTime)
{
	m_stateManager.update(deltaTime);
	m_stateManager.draw();
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	//{
	//	sf::Vector2i mousePos = sf::Mouse::getPosition(getWindow());

	//	int mouseX = mousePos.x;
	//	int mouseY = mousePos.y;

	//	sf::Vector2i gridSize = (sf::Vector2i)m_grid->getSize();

	//	// Only get cell being click on if mouse click is within area of grid
	//	if ((mouseX <= gridSize.x && mouseX >= 0) &&
	//		mouseY <= gridSize.y && mouseY >= 0)
	//	{
	//		Cell& cell = m_grid->getCell(mousePos.x / m_grid->getCellSize(), mousePos.y / m_grid->getCellSize());

	//		if (m_bAddCells)
	//		{
	//			cell.birth();
	//		}
	//		else
	//		{
	//			cell.die();
	//		}
	//	}
	//}

	//if (!m_bPaused && m_genClock.getElapsedTime().asSeconds() >= (m_genDelay * deltaTime))
	//{
	//	m_genClock.restart();
	//	updateCells();
	//}

	//getWindow().draw(*m_grid);
}

void GameOfLife::handleInput(const sf::Event& event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			m_stateManager.pushState(static_cast<int>(GameState::Playing));
		}

		if (event.key.code == sf::Keyboard::A)
		{
			m_stateManager.pushState(static_cast<int>(GameState::Intro));
		}
	}
	//if (event.type == sf::Event::KeyReleased)
	//{
	//	if (event.key.code == sf::Keyboard::E)
	//	{
	//		m_bAddCells = !m_bAddCells;
	//	}

	//	if (event.key.code == sf::Keyboard::P)
	//	{
	//		m_bPaused = !m_bPaused;
	//	}

	//	if (event.key.code == sf::Keyboard::Right)
	//	{
	//		GameSpeed gs = m_gameSpeed;

	//		int nextSpeed = static_cast<int>(gs);
	//		nextSpeed++;
	//		if (nextSpeed <= static_cast<int>(GameSpeed::Full))
	//		{
	//			gs++;
	//			m_gameSpeed = gs;
	//		}

	//		setGenerationDelay(m_gameSpeed);
	//	}

	//	if (event.key.code == sf::Keyboard::Left)
	//	{
	//		GameSpeed gs = m_gameSpeed;

	//		int nextSpeed = static_cast<int>(gs);
	//		nextSpeed--;
	//		if (nextSpeed >= static_cast<int>(GameSpeed::Slow))
	//		{
	//			gs--;
	//			m_gameSpeed = gs;
	//		}

	//		setGenerationDelay(m_gameSpeed);
	//	}

	//	if (event.key.code == sf::Keyboard::R)
	//	{
	//		m_grid->randomizeCells();
	//	}

	//	if (event.key.code == sf::Keyboard::C)
	//	{
	//		m_grid->clearCells();
	//	}
	//}
}

void GameOfLife::setGenerationDelay(const GameSpeed& gs)
{
	switch (gs)
	{
		case GameSpeed::Slow: m_genDelay = 8.f; break;
		case GameSpeed::SlowMedium: m_genDelay = 6.f; break;
		case GameSpeed::Medium: m_genDelay = 4.5f; break;
		case GameSpeed::MediumFast: m_genDelay = 3.f; break;
		case GameSpeed::Fast: m_genDelay = 1.5f; break;
		case GameSpeed::Full: m_genDelay = 0.f; break;
	}
}

void GameOfLife::setGameSettings()
{
	std::string errorMessage = "Invalid input, please enter a valid number";
	int cellSize = getConsoleInputi("Enter Cell Size", errorMessage);
	int gridWidth = getConsoleInputi("Enter Grid width", errorMessage);
	int gridHeight = getConsoleInputi("Enter Grid height", errorMessage);

	m_grid = make_unique<Grid>(gridWidth, gridHeight, cellSize);
}

void GameOfLife::updateCells()
{
	std::vector<CellState>& prevStates = m_grid->getCellStates();

	for (size_t i = 0; i < m_grid->getCells().size(); i++)
	{
		(*m_grid)[i].update(prevStates, *m_grid);
	}

	//parallelFor(0, m_grid->getCells().size(), [this, &prevStates](int i) {
	//	(*m_grid)[i].update(prevStates, *m_grid);
	//});
}

