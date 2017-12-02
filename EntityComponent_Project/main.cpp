#include "Core.h"

int main()
{
	Core game;

	game.initialize();
	game.execute();
	game.deinitialize();

	return 0;
}