#pragma once
#include "State.h"

namespace sf
{
	class Text;
}

class StateManager;

class SplashScreen : public State
{
public:
	SplashScreen(StateManager* manager);
	~SplashScreen();

	virtual void update(float deltaTime) override;

	virtual void draw(sf::RenderWindow& window) override;

	virtual void activate() override;
	virtual void deactivate() override;
	virtual void onCreate()  override;
	virtual void onDestroy() override;

private:
	sf::Text m_text;
};

