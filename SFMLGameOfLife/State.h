#pragma once

namespace sf
{
	class RenderWindow;
	class Event;
}

class StateManager;

class State
{
public:
	State(StateManager* manager);
	virtual ~State();

	// Checks if current state is transparent,
	// If state is transparent, the state beneath it will get rendered as well.
	bool isTransparent() const;

	// Checks if current state is transcendant,
	// If state is transcendant, the state beneath it will get updated as well.
	bool isTranscendant() const;
	bool isActive() const;


	virtual void update(float deltaTime) = 0;

	virtual void draw(sf::RenderWindow& window) = 0;

	// Called when state is activated on state stack.
	virtual void activate() = 0;

	// Called when state is deactivated on state stack.
	virtual void deactivate() = 0;

	// Called when state is created from state manager.
	virtual void onCreate() = 0;

	// Called when state is destroyed from state manager.
	virtual void onDestroy() = 0;

	// Handle input related to state here
	virtual void handleInput(const sf::Event& event) = 0;

protected:
	bool m_bTransparent;
	bool m_bTranscendant;
	bool m_bActive;
	StateManager* m_stateManager;
};

