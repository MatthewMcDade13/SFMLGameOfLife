#pragma once

#include <vector>

namespace sf
{
	class Drawable;
	class RenderTarget;
	class RenderStates;
	typedef Uint32 Uint32;
	typedef Vector2u Vector2u;
}

class Cell;
enum class CellState;

class Grid : public sf::Drawable
{
public:
	/*
	gridWidth = Width of Grid
	gridHeight = Height of Grid
	cellSize = Width and Height of each cell (must be square)
	*/
	Grid(sf::Uint32 gridWidth, sf::Uint32 gridHeight, sf::Uint32 cellSize);
	Grid();
	~Grid();

	Cell& getCell(int x, int y);
	sf::Uint32 getCellIndex(int x, int y) const;
	const std::vector<Cell>& getCells() const;
	sf::Vector2u getCellPosition(int index) const;
	sf::Vector2u getSize() const;
	std::vector<enum class CellState> getCellStates() const;
	sf::Uint32 getCellSize() const;

	void randomizeCells();
	void clearCells();

	int getRowSize() const;
	int getColSize() const;

	void initGridCells();

	void setCellSize(sf::Uint32 cellSize);
	void setGridSize(sf::Uint32 gridWidth, sf::Uint32 gridHeight);

	Cell& operator[](int cellIndex);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void clampCellIndex(int& outIndex) const;

	sf::Uint32 m_cellSize;
	sf::Uint32 m_width;
	sf::Uint32 m_height;

	std::vector<Cell> m_cells;
};

