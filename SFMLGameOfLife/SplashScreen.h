#pragma once
#include "State.h"

namespace sf
{
	class Text;
	class Clock;
}

class StateManager;
struct GameSettings;

class SplashScreen : public State
{
public:
	SplashScreen(StateManager* manager, GameSettings* settings);
	~SplashScreen();

	virtual void update(float deltaTime) override;

	virtual void draw(sf::RenderWindow& window) override;

	virtual void activate() override;
	virtual void deactivate() override;
	virtual void onCreate()  override;
	virtual void onDestroy() override;
	virtual void handleInput(const sf::Event& event) override;

private:
	sf::Text m_text;
	GameSettings* m_settings;
};

