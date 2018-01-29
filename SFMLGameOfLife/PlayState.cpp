#include "stdafx.h"
#include "PlayState.h"
#include "StateManager.h"
#include "Context.h"
#include "GameSettings.h"
#include "Grid.h"
#include "Cell.h"
#include "GameSpeed.h"

using namespace std;

PlayState::PlayState(StateManager* manager, GameSettings* settings)
	: State(manager), m_settings(settings), 
	m_genDelay(0.1f), m_gameSpeed(GameSpeed::Fast),
	m_bAddCells(true), m_grid(nullptr)
{
}


PlayState::~PlayState()
{
}

void PlayState::update(float deltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*m_stateManager->getContext()->window);

		const int mouseX = mousePos.x;
		const int mouseY = mousePos.y;

		const sf::Vector2i gridSize = (sf::Vector2i)m_grid->getSize();

		// Only get cell being click on if mouse click is within area of grid
		if ((mouseX <= gridSize.x && mouseX >= 0) &&
			mouseY <= gridSize.y && mouseY >= 0)
		{
			Cell& cell = m_grid->getCell(mousePos.x / m_grid->getCellSize(), mousePos.y / m_grid->getCellSize());

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

void PlayState::draw(sf::RenderWindow & window)
{
	window.draw(*m_grid);
}

void PlayState::activate()
{
}

void PlayState::deactivate()
{
}

void PlayState::onCreate()
{
	m_grid = make_unique<Grid>(m_settings->gridWidth, m_settings->gridHeight, m_settings->cellSize);
}

void PlayState::onDestroy()
{

}

void PlayState::handleInput(const sf::Event & event)
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
			GameSpeed gs = m_gameSpeed;

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
			GameSpeed gs = m_gameSpeed;

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
			m_grid->randomizeCells();
		}

		if (event.key.code == sf::Keyboard::C)
		{
			m_grid->clearCells();
		}
	}
}

void PlayState::updateCells()
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

void PlayState::setGenerationDelay(GameSpeed gs)
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
