#pragma once

namespace sf
{
	typedef Vector2f Vector2f;
}

class Entity
{
public:
	Entity();
	virtual ~Entity();

	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float velX, float velY);

	sf::Vector2f getVelocity() const;


private:
	sf::Vector2f m_velocity;
};

