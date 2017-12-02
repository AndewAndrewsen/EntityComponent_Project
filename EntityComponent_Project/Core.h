#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Core
{
public:
	Core(void);
	~Core(void);

	void initialize();
	void execute();
	void deinitialize();


	static const int windowWidth = 1366;
	static const int windowHeight = 768;
	static const int bpp = 32;
	static const int AAlevel = 0;
	
	bool quit;
	sf::RenderWindow *window;
	sf::View *view;
	
};

