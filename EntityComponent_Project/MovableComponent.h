#pragma once

#include "Component.h"
#include <SFML\System.hpp>

class MovableComponent : public Component
{
public:
	MovableComponent(Entity* parent): 
	Component(parent) 
	{
		_direction.x = 1;
		_direction.y = 1;
		_speed = 0.5f;
		_name = "MovableComponent";



		jumping = false;
		jumpingPhaseTwo = false;
		lastYPos = 0;
		bool freeFalling = false;
		
			moveRight = false;
			moveLeft = false;

	}

	~MovableComponent() {};

	void update(float deltaTime, sf::RenderWindow *window);

	const sf::Vector2f& direction() const { return _direction; };
	sf::Vector2f& direction() { return _direction; }

	const float& speed() const { return _speed; };
	float& speed() { return _speed; }
	sf::Vector2f	_direction;	
	void setMoveLeft(bool set);
	void setMoveRight(bool set);
	void jump();

	int lastYPos;
	bool jumping;
	bool jumpingPhaseTwo;
	bool moveRight;
	bool moveLeft;
	bool freeFalling;


private:

	
	float			_speed;
};

