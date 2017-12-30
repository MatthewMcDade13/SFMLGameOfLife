#pragma once
#include "State.h"
#include <string>

struct GameSettings;

namespace sf
{
	class Text;
	class Clock;
}

class Grid;
enum class GameSpeed;

class PlayState : public State
{
public:
	PlayState(StateManager* manager, GameSettings* settings);
	~PlayState();

	virtual void update(float deltaTime) override;

	virtual void draw(sf::RenderWindow& window) override;

	virtual void activate() override;
	virtual void deactivate() override;
	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void handleInput(const sf::Event& event) override;

	void updateCells();
	void setGenerationDelay(GameSpeed gs);

private:
	GameSettings* m_settings;

	std::unique_ptr<Grid> m_grid;
	GameSpeed m_gameSpeed;

	bool m_bAddCells;
	bool m_bPaused;
	float m_genDelay;

	sf::Clock m_genClock;
};

