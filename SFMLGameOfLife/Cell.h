#pragma once

#include <vector>
#include <mutex>

namespace sf
{
	class RectangleShape;
	class Drawable;
	class RenderTarget;
	class RenderStates;
	typedef Vector2f Vector2f;
	typedef Vector2u Vector2u;
}

enum class CellState;
class Grid;

class Cell : public sf::RectangleShape
{
public:
	Cell(int size, sf::Vector2u gridPosition, sf::Vector2f position);
	Cell(int size, sf::Vector2u gridPosition);
	Cell(int size);

	Cell(const Cell& other);

	~Cell();

	void update(const std::vector<CellState>& prevStates, const Grid& parentGrid);
	void die();
	void birth();

	sf::Vector2u getGridPosition() const;
	void setGridPosition(sf::Vector2u gridPosition);

	CellState getState() const;

	bool isAlive() const;
	int getAge() const;

private:

	int getAliveNeighbors(const std::vector<CellState>& prevStates, const Grid& parentGrid) const;
	void setDefaultValues();

	enum class CellState m_state;
	int m_age;
	sf::Vector2u m_gridPosition;
	std::mutex m_mutex;
};

