// Jason Mottershead, Student Number 1300455.

// Game class header file.
// This sets up the window for displaying the game.
// All classes will have update calls through this class.

// Header guard.
#ifndef _GAME_H_
#define _GAME_H_

// Include files here.
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <Box2D\Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "level.h"

// The main class that will render the window.
class Game
{

	public:
		// Attributes.
		bool sent_, received_;

		// Methods.
		Game(const float game_screen_width, const float game_screen_height);
		~Game();
		void CheckIfLevelHasFinished();
		void Update();
		void Render();

		// Getters.
		inline sf::RenderWindow* getWindow()	{ return window_; }				// This will return the current game window.

		//// The structure for the game's starting message.
		struct StartMessage
		{
			bool player_team;			// What team the player will be on.
			//sf::Clock game_clock;		// The current game time clock that both clients will base their lag offset from.
			float time;
		};

	private:
		// Attributes.
		const unsigned int frame_rate_= 60;
		const unsigned short port_ = 5000;
		const std::string ip_address_ = "127.0.0.1";
		bool ready_;
		
		b2World* world_;
		sf::Clock clock_;
		sf::Event event_;
		sf::Font font_;
		sf::RenderWindow* window_;
		sf::Time dt_;
		sf::Vector2f screen_resolution_;
		sf::Packet data_;
		sf::TcpSocket player_one_socket_;
		sf::TcpSocket player_two_socket_;
		sf::TcpListener connection_listener_;
		Level level_;

		// Methods.
		void NetworkConnection();
		
		// Overloading packet operator functions.
		// Used for sending packet data.
		// This will allow me to send clock data through packets.
		/*friend sf::Packet& operator <<(sf::Packet& packet, const sf::Clock& clock)
		{
			return packet << clock;
		}*/

		// This will allow me to send struct data through packets.
		friend sf::Packet& operator <<(sf::Packet& packet, const Game::StartMessage& message)
		{
			return packet << message.player_team << message.time;
		}

		// Used for receiving packet data.
		// This will allow me to receive clock data through packets.
		/*friend sf::Packet& operator >>(sf::Packet& packet, sf::Clock clock)
		{
			return packet >> clock;
		}*/

		// This will allow me to receive boolean data through packets.
		/*friend sf::Packet& operator >>(sf::Packet& packet, const bool& player_team)
		{
			return packet >> player_team;
		}*/

		// This will allow me to receive struct data through packets.
		friend sf::Packet& operator >>(sf::Packet& packet, Game::StartMessage& message)
		{
			return packet >> message.player_team >> message.time;
		}
};



#endif