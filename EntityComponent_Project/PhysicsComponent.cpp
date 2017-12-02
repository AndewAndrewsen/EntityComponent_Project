#include "PhysicsComponent.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "MovableComponent.h"

void PhysicsComponent::update(float deltaTime, sf::RenderWindow *window) {
	SpriteComponent* spriteComp = dynamic_cast<SpriteComponent*>(_parent->get("SpriteComponent"));
	MovableComponent* movComp = dynamic_cast<MovableComponent*>(_parent->get("MovableComponent"));

	if(_parent->position().y+spriteComp->size().y < 700) {
		movComp->freeFalling = true;
	} else {
		movComp->freeFalling = false;
	}

	if(movComp->freeFalling)
		_parent->position().y += 1;
	
}

PhysicsComponent::~PhysicsComponent(void)
{
}
