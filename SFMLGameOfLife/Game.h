#pragma once

#include <vector>
#include "ResourceHolder.h"
#include "SharedContext.h"

namespace sf
{
	class RenderWindow;
	class VideoMode;
	class Drawable;
	class Event;
	class Texture;
	class Font;
	class Image;
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

protected:
	ResourceHolder m_resources;
	SharedContext m_context;


	virtual void onGameStart() = 0;

	virtual void update(float deltaTime) = 0;

	virtual void handleInput(const sf::Event& event) = 0;

private:

	sf::RenderWindow m_window;
	std::string m_name;
	bool m_bShowFPS;

};

