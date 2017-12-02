#pragma once

#include <SFML/System.hpp>
#include <map>
#include <string>

class Component;
class VisibleComponent;

namespace sf
{
	class RenderWindow;
}

class Entity
{
public:
	Entity() {};
	~Entity() {};

	void add(Component* ptr);
	Component* get(const std::string& name);

	void update(float deltaTime, sf::RenderWindow &window);
	//void draw(sf::RenderWindow& target);

	const sf::Vector2f& position() const { return _position; }
	sf::Vector2f& position() { return _position; }
	int getHealth();
	void setHealth(int hp);

protected:
	Entity(const Entity&);
	Entity& operator = (const Entity&);

private:
	std::map<std::string, Component*>				_updateComponents;
	std::map<std::string, VisibleComponent*>		_visibleComponents;
	sf::Vector2f									_position;
	int												_health;

};