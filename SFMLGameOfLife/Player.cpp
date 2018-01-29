#include "stdafx.h"
#include "Player.h"
#include "Entity.h"



Player::Player():
	m_entity(nullptr)
{ }

Player::~Player()
{ }

void Player::removeEntity()
{
	m_entity = nullptr;
}

void Player::setEntity(std::unique_ptr<Entity>& entity)
{
	m_entity = std::move(entity);
}

const Entity* Player::getEntity() const
{
	return nullptr;
}

void Player::bindKey(sf::Keyboard::Key key, Action actionBinding)
{
	m_keybinds[key] = actionBinding;
}

void Player::removeBinding(sf::Keyboard::Key key)
{
	m_keybinds.erase(key);
}

void Player::handleLiveInput(float deltaTime)
{
	for (const auto& p : m_keybinds)
	{
		if (sf::Keyboard::isKeyPressed(p.first))
			p.second(deltaTime);
	}
}

