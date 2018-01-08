#pragma once

#include "Game.h"
#include "Grid.h"
#include "StateManager.h"
#include "GameSettings.h"
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
struct GameSettings;

class GameOfLife : public Game
{
public:
	GameOfLife();
	~GameOfLife();

	GameOfLife(const GameOfLife& other) = delete;
	GameOfLife& operator=(const GameOfLife& other) = delete;

private:
	virtual void onGameStart() override;

	virtual void draw() override;

	virtual void update(float deltaTime) override;

	virtual void handleInput(const sf::Event& event) override;


private:

	StateManager m_stateManager;
	GameSettings m_settings;
};

