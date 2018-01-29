#include "stdafx.h"
#include "SplashScreen.h"
#include "StateManager.h"
#include "Context.h"
#include "GameState.h"
#include "PlayState.h"
#include "ToUnderlying.h"
#include "GetConsoleInput.h"
#include "GameSettings.h"

using namespace std;

SplashScreen::SplashScreen(StateManager* manager, GameSettings* settings)
	: State(manager), m_settings(settings)
{
}


SplashScreen::~SplashScreen()
{
}

void SplashScreen::update(float deltaTime)
{
}

void SplashScreen::draw(sf::RenderWindow & window)
{
	window.draw(m_text);
}

void SplashScreen::activate()
{
	std::string message = "Cell Size: " + to_string(m_settings->cellSize) + "\n";
	message += "Grid Width: " + to_string(m_settings->gridWidth) + "\n";
	message += "Grid Height: " + to_string(m_settings->gridHeight) + "\n";
	m_text.setString(message);

	const Context* const context = m_stateManager->getContext();

	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));

	sf::Vector2u windowSize = context->window->getSize();
	m_text.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
}

void SplashScreen::deactivate()
{

}

void SplashScreen::onCreate()
{
	const Context* const context = m_stateManager->getContext();
	const sf::Font& font = context->resources->fontManager.get("./Roboto-Regular.ttf");
	m_text.setFont(font);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(50);
	m_text.setStyle(sf::Text::Bold);

	const std::string errorMessage = "Invalid input, please enter a valid number";
	m_settings->cellSize = getConsoleInputi("Enter Cell Size", errorMessage);
	m_settings->gridWidth = getConsoleInputi("Enter Grid width", errorMessage);
	m_settings->gridHeight = getConsoleInputi("Enter Grid height", errorMessage);
}

void SplashScreen::onDestroy()
{
	std::cout << "Destroying SplashScreen" << std::endl;
}

void SplashScreen::handleInput(const sf::Event& event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			m_stateManager->pushState(GameState::Playing);
		}
	}
}
