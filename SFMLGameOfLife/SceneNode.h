#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> SceneNodePtr;

	SceneNode();
	virtual ~SceneNode();

	void attachChild(SceneNodePtr childNode);

	SceneNodePtr removeChild(const SceneNode& node);

	void update(float deltaTime);

	// Gets transform of enitre scene node - current node as well as children
	sf::Transform getWorldTransform() const;

	// Gets position of enitre scene node - current node as well as children
	sf::Vector2f getWorldPosition() const;

protected:
	// Draws the current Scene Node.
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	// Updates the current Scene Node
	virtual void updateCurrent(float deltaTime);

private:
	SceneNode* m_parent;
	std::vector<SceneNodePtr> m_children;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	void updateChildren(float deltaTime);
};

