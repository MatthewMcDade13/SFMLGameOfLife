#include "stdafx.h"
#include "SplashScreen.h"
#include "StateManager.h"
#include "SharedContext.h"


SplashScreen::SplashScreen(StateManager* manager): State(manager)
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
	std::cout << "Activating SplashScreen" << std::endl;
}

void SplashScreen::deactivate()
{
	std::cout << "Deactivating SplashScreen" << std::endl;
}

void SplashScreen::onCreate()
{
	SharedContext* context = m_stateManager->getContext();
	sf::Font& font = context->resources->fontManager.get("./Roboto-Regular.ttf");
	m_text.setFont(font);
	m_text.setString("AYYY LMAO ITS LIT AF FAM");
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(50);
	m_text.setStyle(sf::Text::Bold);
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));

	sf::Vector2u windowSize = context->window->getSize();

	m_text.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
}

void SplashScreen::onDestroy()
{
	std::cout << "Destroying SplashScreen" << std::endl;
}
