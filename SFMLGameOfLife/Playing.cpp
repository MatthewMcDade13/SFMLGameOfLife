#include "stdafx.h"
#include "Playing.h"
#include "StateManager.h"
#include "SharedContext.h"


Playing::Playing(StateManager* manager) : State(manager)
{
}


Playing::~Playing()
{
}

void Playing::update(float deltaTime)
{
}

void Playing::draw(sf::RenderWindow & window)
{
	window.draw(m_text);
}

void Playing::activate()
{
	std::cout << "Activating Playing" << std::endl;
}

void Playing::deactivate()
{
	std::cout << "Deactivating Playing" << std::endl;
}

void Playing::onCreate()
{
	SharedContext* context = m_stateManager->getContext();
	sf::Font& font = context->resources->fontManager.get("./Roboto-Regular.ttf");
	m_text.setFont(font);
	m_text.setString("OH SHIT IT WORKS");
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(50);
	m_text.setStyle(sf::Text::Bold);
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));

	sf::Vector2u windowSize = context->window->getSize();

	m_text.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
}

void Playing::onDestroy()
{
	std::cout << "Destroying Playing" << std::endl;
}
