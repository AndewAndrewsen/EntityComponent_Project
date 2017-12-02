#pragma once
#include "Component.h"
#include <SFML\System.hpp>

class PlayerComponent : public Component
{
public:
	PlayerComponent(Entity* parent) : Component(parent)
	{
		_name = "PlayerComponent";
	}
	~PlayerComponent() {}


	void update(float deltaTime);

	float& speed() {return _speed; }
	sf::Vector2f& direction() {return _direction; }

private:
	float	_speed;
	sf::Vector2f	_direction;
};

