#include "ClickableComponent.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include <SFML/System.hpp>

ClickableComponent::~ClickableComponent(void)
{
}




void ClickableComponent::update(float deltaTime, sf::RenderWindow* app)
{
	if ( _parent )
	{
		sf::Event event;
		//const sf::Mouse& input = sf::Mouse();
		SpriteComponent* sprComp = dynamic_cast<SpriteComponent*>(_parent->get("SpriteComponent"));

		while(app->pollEvent(event))
		{
				if(event.type == sf::Event::MouseButtonPressed)
					{
						if(event.mouseButton.button == sf::Mouse::Left)
						{
				
							if(sf::Mouse::getPosition(*app).x > _parent->position().x && sf::Mouse::getPosition(*app).x < (_parent->position().x+sprComp->getSpriteWidth()))
							{
								if(sf::Mouse::getPosition(*app).y > _parent->position().y && sf::Mouse::getPosition(*app).y < (_parent->position().y+sprComp->getSpriteHeight()))
								{
				
											clicked = true;
								}
							}
					}
				}
			
			}
		}
}

bool ClickableComponent::getState()
{
	return clicked;
}