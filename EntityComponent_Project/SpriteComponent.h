#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

class SpriteComponent : public VisibleComponent
{
public:
	SpriteComponent(Entity* parent) : VisibleComponent(parent) { _name = "SpriteComponent";}
	~SpriteComponent() {}

	void update(float deltaTime, sf::RenderWindow* window);
	void draw(sf::RenderWindow& target);

	sf::Vector2f size() const { return (sf::Vector2f)_sprite.getTexture()->getSize(); }

	void setImage(const sf::Texture& source) { _sprite.setTexture(source);}
	void changeImageCenterToOrigin(int imgW, int imgH);
	void rotateImage(float angle);

	int getSpriteWidth();
	int getSpriteHeight();
private:
	sf::Sprite		_sprite;
};