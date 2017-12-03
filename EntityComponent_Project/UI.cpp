#include "UI.h"


UI::UI(void)
{
	size = 10;
	
}


UI::~UI(void)
{
}

void UI::setFont(sf::Font valFont)
{
	font = valFont;
}

void UI::write(std::string _text)
{
	
	text.setString(_text);	
}

void UI::update(sf::RenderWindow &window, sf::View &view)
{
	text.setPosition(view.getCenter().x-posX, view.getCenter().y-posY);
	window.draw(text);

}

void UI::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}