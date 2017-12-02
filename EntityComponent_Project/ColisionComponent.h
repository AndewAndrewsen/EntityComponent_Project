#pragma once

#include <list>
#include "MovableComponent.h"
#include "SpriteComponent.h"

class ColisionComponent : public Component
{
public:
	ColisionComponent(Entity* parent) : Component(parent) 
	{
		_name = "ColisionComponent";
		entList.push_back(parent);

		/* --- May be needed for protecting multiple entities in the list;
		for(int i = 0; i <= entList.size(); i++)
		{

		}
		*/
	}
	~ColisionComponent() {}

	void update(float deltaTime, sf::RenderWindow *window);

	sf::Vector2f& bounds() { return _bounds; }
	sf::Vector2f& world() { return _world; }

private:
	sf::Vector2f		_bounds;
	sf::Vector2f		_world;
	sf::Vector2f		_SpikeBox;
	std::list<Entity*> entList;
};

