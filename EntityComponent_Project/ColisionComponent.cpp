#include "ColisionComponent.h"
#include "Entity.h"


void ColisionComponent::update(float deltaTime, sf::RenderWindow *window)
{
	if ( _parent )
	{
		MovableComponent* comp = dynamic_cast<MovableComponent*>(_parent->get("MovableComponent"));
		SpriteComponent* compSprite = dynamic_cast<SpriteComponent*>(_parent->get("SpriteComponent"));


		

		/*if(_parent->position().x + compSprite->size().x > 1366)
		{
			comp->direction().x = -1;
		}
		if(_parent->position().x < 0) 
		{
			comp->direction().x = 1;
		}
		if(_parent->position().y < 0) {
			comp->direction().y = 1;
		}
		if(_parent->position().y + compSprite->size().y > 768) 
		{
			comp->direction().y = -1;
		}*/
	}
}