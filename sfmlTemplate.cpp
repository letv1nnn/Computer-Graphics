#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main() {
	// Window
	sf::RenderWindow window(sf::VideoMode(640, 480), 
		"Window", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	// Game Loop
	while (window.isOpen()) {
		// Event Polling
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed: 
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
						window.close();
					break;
			}
		}

		// Update


		// Render
		window.clear(sf::Color::White); // clear old frame

		// Game drawing section

		window.display(); // Tell app that window is done deawing

	}


	// End of application
	return 0;
}
