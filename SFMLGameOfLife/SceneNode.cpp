#include "stdafx.h"
#include "SceneNode.h"

SceneNode::SceneNode()
{
}


SceneNode::~SceneNode()
{
}

void SceneNode::attachChild(SceneNodePtr childNode)
{
	childNode->m_parent = this;
	m_children.push_back(std::move(childNode));
}

SceneNode::SceneNodePtr SceneNode::removeChild(const SceneNode& node)
{
	auto foundIt = std::find_if(m_children.begin(), m_children.end(), [&node](SceneNodePtr& n) { 
		return n.get() == &node;
	});

	if (foundIt == m_children.end()) return nullptr;

	SceneNodePtr result = std::move(*foundIt);
	result->m_parent = nullptr;
	m_children.erase(foundIt);

	return std::move(result);
}


void SceneNode::updateCurrent(float deltaTime) { }

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);

	drawChildren(target, states);
}

void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto& child : m_children)
	{
		child->draw(target, states);
	}
}

void SceneNode::update(float deltaTime)
{
	updateCurrent(deltaTime);

	updateChildren(deltaTime);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (auto node = this; node != nullptr; node = node->m_parent)
	{
		transform *= getTransform();
	}

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	// convert transform to Vector2f to get position
	return getWorldTransform() * sf::Vector2f();
}

void SceneNode::updateChildren(float deltaTime)
{
	for (auto& child : m_children)
	{
		child->update(deltaTime);
	}
}
