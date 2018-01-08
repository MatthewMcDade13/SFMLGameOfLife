#pragma once

#include "SceneNode.h"

namespace sf
{
	typedef Vector2f Vector2f;
}

class Entity : public SceneNode
{
public:
	Entity();
	virtual ~Entity();
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float velX, float velY);

	sf::Vector2f getVelocity() const;

protected:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const = 0;

private:
	sf::Vector2f m_velocity;
};

