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
		const sf::Input& input = app->GetInput();
		SpriteComponent* sprComp = dynamic_cast<SpriteComponent*>(_parent->get("SpriteComponent"));

		while(app->GetEvent(event))
		{
				if(event.Type == sf::Event::MouseButtonPressed)
					{
						if(event.MouseButton.Button == sf::Mouse::Left)
						{
							if(input.GetMouseX() > _parent->position().x && input.GetMouseX() < (_parent->position().x+sprComp->getSpriteWidth()))
							{
								if(input.GetMouseY() > _parent->position().y && input.GetMouseY() < (_parent->position().y+sprComp->getSpriteHeight()))
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