#include "Game.h"

// Private methods
void Game::initVariables() {
	this->window = nullptr;
}

void Game::initWindow() {
	this->videomode.width = 800;
	this->videomode.height = 600;
	this->window = new sf::RenderWindow(
		videomode, "AIM trainer", 
		sf::Style::Titlebar | sf::Style::Close);
}

// Constructor
Game::Game() {
	initVariables();
	initWindow();
}

// Destructor
Game::~Game() {
	delete this->window;
}


// Methods

const bool Game::running() const {
	return window->isOpen();
}

void Game::pollEvents() {
	while (this->window->pollEvent(event)) {
		switch (this->event.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::update() {
	pollEvents();
}

void Game::render() {
	this->window->clear(sf::Color::Yellow);

	// Draw Game Objects

	this->window->display();
}

