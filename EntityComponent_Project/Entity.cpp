#include "Entity.h"
#include "Component.h"

#include <SFML\Graphics.hpp>

void Entity::add(Component* ptr)
{
	VisibleComponent* vis = dynamic_cast<VisibleComponent*>(ptr);

	if( vis != nullptr)
	{
		if ( _visibleComponents.find(ptr->name()) == _visibleComponents.end() )
		{
			_visibleComponents.insert(std::make_pair(ptr->name(), vis));
		}
	}
	else
	{
		if ( _updateComponents.find(ptr->name()) == _updateComponents.end() )
		{
			_updateComponents.insert(std::make_pair(ptr->name(), ptr));
		}
	}
}
	
Component* Entity::get(const std::string& name)
{
	if (_visibleComponents.find(name) != _visibleComponents.end() )
	{
		return _visibleComponents[name];
	}
	else if(_updateComponents.find(name) != _updateComponents.end() )
	{
		return _updateComponents[name];
	}

	return nullptr;
};

void Entity::update(float deltaTime, sf::RenderWindow &window)
{
	std::map<std::string, Component*>::iterator itr1 = _updateComponents.begin();
	std::map<std::string, VisibleComponent*>::iterator itr2 = _visibleComponents.begin();

	while( itr1 != _updateComponents.end() )
	{
		itr1->second->update(deltaTime, &window);
		itr1++;
	}

	while( itr2 != _visibleComponents.end() )
	{
		itr2->second->update(deltaTime, &window);
		itr2->second->draw(window);
		itr2++;
	}
}

/*
void Entity::draw(sf::RenderWindow& target)
{
	std::map<std::string, VisibleComponent*>::iterator itr2 = _visibleComponents.begin();

	while( itr2 != _visibleComponents.end() )
	{
		itr2->second->draw(target);
		itr2++;
	}
}*/

int Entity::getHealth() {
		return _health;
}

void Entity::setHealth(int hp) {
		 _health = hp;
}