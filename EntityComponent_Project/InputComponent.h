#pragma once

#include "Component.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/graphics.hpp>

class InputComponent : public Component
{
public:
	InputComponent(Entity *parent):
	  Component(parent) 
	  {
		  _name = "InputComponent";
		  input = new sf::Keyboard();
	  }
	sf::Keyboard *input;
	sf::Keyboard::Key keyCode;
	void takeInput(sf::RenderWindow* window);
	void update(float deltaTime);


	~InputComponent(void);
};

