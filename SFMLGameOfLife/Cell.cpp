#include "stdafx.h"
#include "Cell.h"
#include "Grid.h"
#include "CellState.h"

Cell::Cell(int size, sf::Vector2u gridPosition, sf::Vector2f position)
	: RectangleShape(sf::Vector2f((float)size, (float)size)), m_gridPosition(gridPosition), m_state(CellState::Dead)
{	
	setDefaultValues();
	setPosition(position);
}

Cell::Cell(int size, sf::Vector2u gridPosition)
	: RectangleShape(sf::Vector2f((float)size, (float)size)), m_gridPosition(gridPosition), m_state(CellState::Dead)
{
	setDefaultValues();
}

Cell::Cell(int size): RectangleShape(sf::Vector2f((float)size, (float)size)), m_state(CellState::Dead)
{
	setDefaultValues();
}

Cell::Cell(const Cell& other)
	: RectangleShape(other),
	m_state(other.m_state), m_age(other.m_age),
	m_gridPosition(other.m_gridPosition), m_mutex()
{
}

Cell::~Cell()
{
}

sf::Vector2u Cell::getGridPosition() const
{
	return m_gridPosition;
}

void Cell::setGridPosition(sf::Vector2u gridPosition)
{
	m_gridPosition = gridPosition;
}

CellState Cell::getState() const
{
	return m_state;
}

bool Cell::isAlive() const
{
	return m_state == CellState::Alive;
}

int Cell::getAge() const
{
	return m_age;
}

void Cell::update(const std::vector<CellState>& prevStates, const Grid& currentGrid)
{
	int neighborCount = getAliveNeighbors(prevStates, currentGrid);

	if (isAlive())
	{
		if (neighborCount < 2 || neighborCount > 3)
		{
			die();
		}
	}
	else
	{
		if (neighborCount == 3)
		{
			birth();
		}
	}
}

int Cell::getAliveNeighbors(const std::vector<CellState>& prevStates, const Grid& currentGrid) const
{
	int xPos = m_gridPosition.x;
	int yPos = m_gridPosition.y;

	int neighborCount = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0) continue;

			int cellIndex = currentGrid.getCellIndex(xPos + i, yPos + j);
			CellState neighborState = prevStates[cellIndex];

			if (neighborState == CellState::Alive)
			{
				neighborCount++;
			}
		}
	}

	return neighborCount;
}

void Cell::die()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	m_state = CellState::Dead;
	setDefaultValues();
}

void Cell::birth()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	m_state = CellState::Alive;
	setFillColor(sf::Color(67, 31, 31));
}


void Cell::setDefaultValues()
{
	setFillColor(sf::Color::Transparent);
	setOutlineColor(sf::Color(105, 105, 105, 255));
	//setOutlineThickness(0.5f);
}

