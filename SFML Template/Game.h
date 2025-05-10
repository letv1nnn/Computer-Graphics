#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game {
private:
	// Private vars
	// window
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event event;

	// private methods 
	void initVariables();
	void initWindow();
public:
	// Constructor / Distructor;
	Game();
	virtual ~Game();

	// methods
	const bool running() const;

	void pollEvents();
	void update();
	void render();
};
