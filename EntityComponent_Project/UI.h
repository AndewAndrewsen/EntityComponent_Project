#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "resources.h"

class UI : public resources
{
public:
	UI(void);
	~UI(void);

	void setFont(sf::Font valFont);
	void write(std::string _text);
	void update(sf::RenderWindow &window, sf::View &view);
	void setPosition(int x, int y);

private:
	sf::Font font;
	sf::Text text; 
	int size;
	int posX;
	int posY;
};

