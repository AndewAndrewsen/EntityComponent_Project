#include "MovableComponent.h"
#include "Entity.h"

void MovableComponent::update(float deltaTime, sf::RenderWindow *window)
{


	if ( _parent )
	{
		if(moveLeft)
			_parent->position().x -= _speed;

		if(moveRight)
			_parent->position().x += _speed;

		MovableComponent::jump();
	}
}


void MovableComponent::setMoveLeft(bool set) {
	moveLeft = set;
}

void MovableComponent::setMoveRight(bool set) {
		moveRight = set;
	}


void MovableComponent::jump() {
	
	if(jumping && !jumpingPhaseTwo && !freeFalling) {
		lastYPos = _parent->position().y;
		jumping = false;
		jumpingPhaseTwo = true;
	}
	if(jumpingPhaseTwo) {
		_parent->position().y -= 3;
		 if((lastYPos - _parent->position().y) >= 250)
		 {
			jumpingPhaseTwo = false;
		 }

	}

}