#pragma once

#include "Component.h"

#include <SFML\Window\Input.hpp>
#include <SFML\graphics.hpp>

class InputComponent : public Component
{
public:
	InputComponent(Entity *parent):
	  Component(parent) 
	  {
		  _name = "InputComponent";
		  input = new sf::Input();
	  }
	sf::Input *input;
	sf::Key::Code keyCode;
	void takeInput(sf::RenderWindow* window);
	void update(float deltaTime);


	~InputComponent(void);
};

