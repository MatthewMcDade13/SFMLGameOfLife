#pragma once

#include "Game.h"
#include "Grid.h"
#include "StateManager.h"
#include <atomic>
#include <memory>

namespace sf
{
	class Font;
	class Clock;
	class Text;
}

enum class GameSpeed;
class StateManager;

class GameOfLife : public Game
{
public:
	GameOfLife();
	~GameOfLife();

	GameOfLife(const GameOfLife& other) = delete;
	GameOfLife& operator=(const GameOfLife& other) = delete;

	void setGameSettings();

private:
	virtual void onGameStart() override;

	virtual void update(float deltaTime) override;

	virtual void handleInput(const sf::Event& event) override;

	void setGenerationDelay(const GameSpeed& gs);


private:

	void updateCells();

	std::unique_ptr<Grid> m_grid;
	GameSpeed m_gameSpeed;
	StateManager m_stateManager;

	bool m_bAddCells;
	bool m_bPaused;
	float m_genDelay;

	sf::Clock m_genClock;
};

