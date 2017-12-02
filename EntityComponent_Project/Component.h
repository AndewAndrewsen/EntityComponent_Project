#pragma once

#include <string>

class Entity;

namespace sf
{
	class RenderWindow;
}

class Component
{
public:
	Component(Entity* parent) : _parent(parent){}

	virtual ~Component() {}
	virtual void update(float deltaTime, sf::RenderWindow* window) = 0;
	const std::string& name() const {return _name;};
	Entity* const parent() const { return _parent;};

protected:
	std::string _name;
	Entity* _parent;
};

class VisibleComponent : public Component
{
public:
	VisibleComponent(Entity* parent) : Component(parent){}

	virtual ~VisibleComponent() {}
	virtual void draw(sf::RenderWindow& target) = 0;
};