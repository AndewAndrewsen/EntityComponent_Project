#include "SpriteComponent.h"
#include "Entity.h"

#include <math.h>

void SpriteComponent::update(float deltaTime, sf::RenderWindow* window)
{
	if( _parent != nullptr )
	{
		_sprite.setPosition(_parent->position());
	}
}

void SpriteComponent::draw(sf::RenderWindow& target)
{
	target.draw(_sprite);
}

void SpriteComponent::changeImageCenterToOrigin(int imgW, int imgH)
{
	
	_sprite.setOrigin(imgW/2, imgH/2);
}

void SpriteComponent::rotateImage(float angle)
{
	_sprite.rotate(angle);
}

int SpriteComponent::getSpriteWidth()
{
	return _sprite.getTexture()->getSize().x;
}

int SpriteComponent::getSpriteHeight()
{
	return _sprite.getTexture()->getSize().y;
}