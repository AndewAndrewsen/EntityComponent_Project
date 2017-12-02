#pragma once
#include "component.h"


class PhysicsComponent :
	public Component
{
public:
	PhysicsComponent(Entity* parent) :
	  Component(parent)
	  {
		  _name = "PhysicsComponent";
	  }


	  void update(float deltaTime, sf::RenderWindow *window);


	~PhysicsComponent(void);
};

