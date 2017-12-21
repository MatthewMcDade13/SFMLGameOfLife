#include "stdafx.h"
#include "GameOfLife.h"
#include "Grid.h"
#include "Cell.h"
#include "CellState.h"
#include "GameSpeed.h"
#include "ResourceManager.h"
#include "parallelFor.h"
//#include <ppl.h> 


GameOfLife::GameOfLife(): m_genDelay(0.1f), m_gameSpeed(GameSpeed::Fast), m_bAddCells(true)
{
}


GameOfLife::~GameOfLife()
{
}

void GameOfLife::onGameStart()
{
	m_grid.setCellSize(5);
	m_grid.setGridSize(1000, 1000);
	m_grid.initGridCells();

	addDrawable(&m_grid);

	// TODO: Make a display 'hud' for showing controls 
	// and state of game

	//sf::Text infoText;

	//infoText.setFont(m_fontMan.get("./Roboto-Regular.ttf"));

	//std::string info = "";

	//info += "Add Cell: ON\n";
	//info += "Speed: FAST\n\n";
	//info += "Controls: \n";
	//info += "E: Toggle Add/Remove Cells\n";
	//info += "P: Pause\n";
	//info += "<- Decrease Speed\n";
	//info += "-> Increase Speed\n";
	//info += "Click on cells to add/remove";

	//infoText.setString(info);
	//infoText.setCharacterSize(15);
	//infoText.setFillColor(sf::Color(255,255,255,69));
	//infoText.setStyle(sf::Text::Bold);

	//m_infoText = infoText;


	//addDrawable(&(m_infoText.load()));

}

void GameOfLife::update(float deltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(getWindow());

		int mouseX = mousePos.x;
		int mouseY = mousePos.y;

		sf::Vector2i gridSize = (sf::Vector2i)m_grid.getSize();

		// Only get cell being click on if mouse click is within area of grid
		if ((mouseX <= gridSize.x && mouseX >= 0) &&
			mouseY <= gridSize.y && mouseY >= 0)
		{
			Cell& cell = m_grid.getCell(mousePos.x / m_grid.getCellSize(), mousePos.y / m_grid.getCellSize());

			if (m_bAddCells)
			{
				cell.birth();
			}
			else
			{
				cell.die();
			}
		}
	}

	if (!m_bPaused && m_genClock.getElapsedTime().asSeconds() >= (m_genDelay * deltaTime))
	{
		m_genClock.restart();
		updateCells();
	}
}

void GameOfLife::handleInput(const sf::Event& event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::E)
		{
			m_bAddCells = !m_bAddCells;
		}

		if (event.key.code == sf::Keyboard::P)
		{
			m_bPaused = !m_bPaused;
		}

		if (event.key.code == sf::Keyboard::Right)
		{
			GameSpeed gs = m_gameSpeed.load();

			int nextSpeed = static_cast<int>(gs);
			nextSpeed++;
			if (nextSpeed <= static_cast<int>(GameSpeed::Full))
			{
				gs++;
				m_gameSpeed = gs;
			}

			setGenerationDelay(m_gameSpeed);
		}

		if (event.key.code == sf::Keyboard::Left)
		{
			GameSpeed gs = m_gameSpeed.load();

			int nextSpeed = static_cast<int>(gs);
			nextSpeed--;
			if (nextSpeed >= static_cast<int>(GameSpeed::Slow))
			{
				gs--;
				m_gameSpeed = gs;
			}

			setGenerationDelay(m_gameSpeed);
		}

		if (event.key.code == sf::Keyboard::R)
		{
			m_grid.randomizeCells();
		}

		if (event.key.code == sf::Keyboard::C)
		{
			m_grid.clearCells();
		}
	}
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

void GameOfLife::updateCells()
{
	std::vector<CellState>& prevStates = m_grid.getCellStates();

	parallelFor(0, m_grid.getCells().size(), [this, &prevStates](int i) {
		m_grid[i].update(prevStates, m_grid);
	});
}

