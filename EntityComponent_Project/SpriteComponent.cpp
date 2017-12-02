#include "SpriteComponent.h"
#include "Entity.h"

#include <math.h>

void SpriteComponent::update(float deltaTime, sf::RenderWindow* window)
{
	if( _parent != nullptr )
	{
		_sprite.SetPosition(_parent->position());
	}
}

void SpriteComponent::draw(sf::RenderWindow& target)
{
	target.Draw(_sprite);
}

void SpriteComponent::changeImageCenterToOrigin(int imgW, int imgH)
{
	_sprite.SetCenter(imgW/2, imgH/2);
}

void SpriteComponent::rotateImage(float angle)
{
	_sprite.Rotate(angle);
}

int SpriteComponent::getSpriteWidth()
{
	return _sprite.GetImage()->GetWidth();
}

int SpriteComponent::getSpriteHeight()
{
	return _sprite.GetImage()->GetHeight();
}