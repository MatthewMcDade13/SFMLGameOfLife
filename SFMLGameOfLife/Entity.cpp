#include "stdafx.h"
#include "Entity.h"


Entity::Entity(): m_velocity({0.f,0.f})
{
}


Entity::~Entity()
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

void Entity::setVelocity(float velX, float velY)
{
	m_velocity = sf::Vector2f(velX, velY);
}

sf::Vector2f Entity::getVelocity() const
{
	return m_velocity;
}
