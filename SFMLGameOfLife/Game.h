#pragma once

#include <vector>
#include "ResourceHolder.h"
#include "Context.h"

namespace sf
{
	class RenderWindow;
	class VideoMode;
	class Drawable;
	class Event;
	class Texture;
	class Font;
	class Image;
	class Time;
}

template<typename T>
class ResourceManager;

struct ResourceHolder;

class Game
{
public:
	Game();
	Game(const Game& g) = delete;
	virtual ~Game();

	Game& operator=(const Game& g) = delete;

	sf::RenderWindow& getWindow();

	void createWindow(const sf::VideoMode vm, const std::string& title);

	void start();

	void setFPS(bool show);

	void setFrameTime(float framesPerSecond);

	void setUseFixedTimeStep(bool shouldUseTimeStep);

protected:
	ResourceHolder m_resources;
	Context m_context;

	virtual void onGameStart() = 0;

	virtual void draw() = 0;

	virtual void update(float deltaTime) = 0;

	virtual void handleInput(const sf::Event& event) = 0;

private:

	sf::RenderWindow m_window;
	std::string m_name;
	bool m_bShowFPS;
	bool m_bUseFixedTimeStep;
	sf::Time m_timePerFrame;

	void processInput();
	void render();

};

