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
#include <SFML/Network.hpp>
#include "level.h"
#include "network.h"

class Game
{

	public:
		// Methods.
		Game(const int game_screen_width, const int game_screen_height);
		~Game();
		void Update();

	private:
		// Attributes.
		const unsigned int kFrameRate= 60;	
		b2World* world_;
		sf::Clock clock_;
		sf::Event event_;
		sf::Font font_;
		sf::Time dt_;
		sf::Vector2f screen_resolution_;
		sf::TcpSocket player_one_socket_;
		sf::TcpSocket player_two_socket_;
		Level level_;
		Network network_;

		// Methods.
		void CheckIfLevelHasFinished();
		void StartAcceptingConnections();
	
};



#endif