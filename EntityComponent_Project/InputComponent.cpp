#include "InputComponent.h"
#include "Entity.h"

void InputComponent::takeInput(sf::RenderWindow* window)
{
//	sf::RenderWindow window;
		sf::Event Event;
/*			while(window->GetEvent(Event))
		{
			/*if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::))
			{
				_parent->position().x -= 10;
			}*/
	//	}
		
	
		
}

void InputComponent::update(float deltaTime)
{
//	InputComponent::takeInput();

}

InputComponent::~InputComponent(void)
{
}
