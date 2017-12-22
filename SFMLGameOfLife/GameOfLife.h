#pragma once

#include "Game.h"
#include "Grid.h"
#include <atomic>

namespace sf
{
	class Font;
	class Clock;
	class Text;
}

enum class GameSpeed;

class GameOfLife : public Game
{
public:
	GameOfLife();
	~GameOfLife();

	void setGameSettings();

private:
	virtual void onGameStart() override;

	virtual void update(float deltaTime) override;

	virtual void handleInput(const sf::Event& event) override;

	void setGenerationDelay(const GameSpeed& gs);


private:

	void updateCells();

	Grid m_grid;
	bool m_bAddCells;
	bool m_bPaused;
	GameSpeed m_gameSpeed;
	float m_genDelay;

	sf::Clock m_genClock;
};

