#pragma once
#include <SFML/Window.hpp>
#include "Component.h"


class ClickableComponent : public Component
{
public:
	ClickableComponent(Entity* parent) : Component(parent) 
	{

		_name = "ClickableComponent";
		clicked = false;
/*		x = parent->position().x;
		y = parent->position().y;
		comp = dynamic_cast<SpriteComponent*>(parent->get("SpriteComponent"));
		width = comp->getSpriteWidth();
		height = comp->getSpriteHeight();*/
		
	}
	~ClickableComponent(void);
	
	void update(float deltaTime, sf::RenderWindow* window);
	bool getState();
	

private:
	bool clicked;
	int x, y;
	int width, height;
};

