#include "stdafx.h"
#include "Grid.h"
#include "CellState.h"
#include "Cell.h"
#include <time.h>

using namespace std;

Grid::Grid(sf::Uint32 gridWidth, sf::Uint32 gridHeight, sf::Uint32 cellSize)
	:m_cells(vector<unique_ptr<Cell>>((gridWidth / cellSize) * (gridWidth / cellSize))), 
	m_width(gridWidth), m_height(gridHeight), m_cellSize(cellSize)
{
	int rowSize = getRowSize();

	srand(time(NULL));

	for (size_t i = 0; i < m_cells.size(); i++)
	{
		unique_ptr<Cell> cell = make_unique<Cell>(m_cellSize, sf::Vector2u(i % rowSize, i / rowSize));

		if (i == 0)
		{
			cell->setPosition(0.f, 0.f);
		}
		else
		{
			Cell& prevCell = *m_cells[i - 1];
			sf::Vector2f prevCellPos = prevCell.getPosition();

			if (prevCellPos.x + m_cellSize >= m_width)
			{
				cell->setPosition(0.f, prevCellPos.y + (float)m_cellSize);
			}
			else
			{
				cell->setPosition(prevCellPos.x + (float)m_cellSize, prevCellPos.y);
			}

			int roll = rand() % 100 + 1;

			if (roll <= 25) cell->birth();
		}

		m_cells[i] = std::move(cell);
	}
}

Grid::~Grid()
{
}

Grid::Grid(const Grid& other)
	: m_width(other.m_width), m_height(other.m_height),
	m_cells(vector<unique_ptr<Cell>>(other.m_cells.size()))
{
	for (size_t i = 0; i < other.m_cells.size(); i++)
	{
		m_cells[i] = make_unique<Cell>(*other.m_cells[i]);
	}
}

Grid& Grid::operator=(const Grid& right)
{
	if (&right == this)
		return *this;

	m_cellSize = right.m_cellSize;
	m_width = right.m_width;
	m_height = right.m_height;

	for (size_t i = 0; i < right.m_cells.size(); i++)
	{
		m_cells[i] = make_unique<Cell>(*right.m_cells[i]);
	}
	return *this;
}

Cell& Grid::getCell(int x, int y)
{
	int pos = getCellIndex(x, y);

	return *m_cells[pos];
}

sf::Uint32 Grid::getCellIndex(int x, int y) const
{

	int rowSize = getRowSize();

	int pos = (y * rowSize) + x;

	clampCellIndex(pos);

	return pos;
}

const vector<unique_ptr<Cell>>& Grid::getCells() const
{
	return m_cells;
}

sf::Vector2u Grid::getCellPosition(int index) const
{
	clampCellIndex(index);
	int gridWidth = getRowSize();

	return sf::Vector2u(index % gridWidth, index / gridWidth);
}

sf::Vector2u Grid::getSize() const
{
	return sf::Vector2u(m_width, m_height);
}

vector<CellState> Grid::getCellStates() const
{
	vector<CellState> states(m_cells.size());
	for (size_t i = 0; i < m_cells.size(); i++)
	{
		states[i] = (m_cells[i]->getState());
	}

	return move(states);
}

sf::Uint32 Grid::getCellSize() const
{
	return m_cellSize;
}

void Grid::randomizeCells()
{
	clearCells();
	srand(time(NULL));

	for (size_t i = 0; i < m_cells.size(); i++)
	{
		int roll = rand() % 100 + 1;

		if (roll <= 25) m_cells[i]->birth();
	}
}

void Grid::clearCells()
{
	for (size_t i = 0; i < m_cells.size(); i++)
	{
		m_cells[i]->die();
	}
}

int Grid::getRowSize() const
{
	return m_width / m_cellSize;
}

int Grid::getColSize() const
{
	return m_height / m_cellSize;
}

void Grid::setCellSize(sf::Uint32 cellSize)
{
	m_cellSize = cellSize;
}

void Grid::setGridSize(sf::Uint32 gridWidth, sf::Uint32 gridHeight)
{
	m_width = gridWidth;
	m_height = gridHeight;
}


Cell& Grid::operator[](int cellIndex)
{
	return *m_cells[cellIndex];
}

void Grid::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (size_t i = 0; i < m_cells.size(); i++)
	{
		target.draw(*m_cells[i]);
	}
}

void Grid::clampCellIndex(int& outIndex) const
{

	if (outIndex >= (int)m_cells.size())
	{
		outIndex -= (int)m_cells.size();
	}
	else if (outIndex < 0)
	{
		outIndex += (int)m_cells.size();
	}
}

