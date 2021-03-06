// Jason Mottershead, Student Number 1300455.

// Game class header file.
// This sets up the window for displaying the game.
// All classes will have update calls through this class.

// Header guard.
#ifndef _GAME_H_
#define _GAME_H_

// Include files here.
#include <iostream>
#include <Box2D\Box2D.h>
#include <SFML/Graphics.hpp>
#include "init_state.h"

class Game
{

	public:
		// Methods.
		Game(const int game_screen_width, const int game_screen_height);
		~Game();
		void Update();
		void Render();

		// Getters.
		// This will return the current game window.
		inline sf::RenderWindow* getWindow()	{ return window_; }				

	private:
		// Attributes.
		const unsigned int kFrameRate = 60;
		b2World* world_;
		sf::Clock clock_;
		sf::Event event_;
		sf::Font font_;
		sf::RenderWindow* window_;
		sf::Time dt_;
		sf::Vector2f screen_resolution_;
		State* current_state_;

		// Methods.
		void HandleStates();

};

#endif