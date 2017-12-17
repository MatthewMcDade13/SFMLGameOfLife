#pragma once

#include <vector>
#include "ResourceManager.h"

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
	ResourceManager<sf::Texture> m_textureMan;
	ResourceManager<sf::Font> m_fontMan;
	ResourceManager<sf::Image> m_imageMan;

	virtual void onGameStart() = 0;

	virtual void update(float deltaTime) = 0;

	virtual void handleInput(const sf::Event& event) = 0;

	void addDrawable(sf::Drawable* drawable);

private:
	void render();

	sf::RenderWindow m_window;
	std::vector<sf::Drawable*> m_drawables;
	std::string m_name;
	bool m_bShowFPS;

};

