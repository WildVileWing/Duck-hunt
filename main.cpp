#include <iostream>

#include "Game.h"

//using namespace sf;

int main() {
	//Initialize Game engine
	Game game;

	//Initialize srand
	std::srand(static_cast<unsigned>(time(NULL)));

	//Game loop
	while (game.running()) 
	{
		//Update
		game.update();
			
		//Render
		game.render();
	}

	//End when window is closed
	return 0;
}