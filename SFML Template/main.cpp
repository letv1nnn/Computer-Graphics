#include <iostream>
#include "Game.h"


int main() {
	// Init game engine
	Game game;

	// Game Loop
	while (game.running()) {
		// Update
		game.update();

		// Render
		game.render();
	}


	// End of application
	return 0;
}
