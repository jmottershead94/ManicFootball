// Jason Mottershead, 1300455.

// State class header file.
// This is the base state class, every other state class will inherit from this.
// This will set the template up for the rest of the states.

// Header guard.
#ifndef _STATE_H_
#define _STATE_H_

// Include files here.
#include <iostream>
#include <string>
#include <Box2D\Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include "network.h"

// The base state class, will be used by all other states.
class State
{

	public:
		// Methods.
		virtual ~State() {};

		// Pure virtual functions that every state MUST have.
		// Intended to be overwritten by the more specific states.
		
		// Handling input for reading input through states.
		virtual State* HandleInput() = 0;

		// Providing each state with its' own entering sequence.
		virtual void OnEnter() = 0;

		// Providing each state with its' own exiting sequence.
		virtual void OnExit() = 0;

		// Render for rendering any specific text/objects for that state.
		virtual void Render() = 0;

		// Not a pure virtual function because when a state cleans up, it should go back here.
		// All of the pointers will be erased.
		virtual void Cleanup();
		virtual void Update(float dt);

	protected:
		// Attributes.
		const unsigned short port_ = 5000;
		const std::string server_ip_address_ = "127.0.0.1";
		b2World* world_;
		sf::Font* font_;
		sf::RenderWindow* window_;
		sf::Text* text_;
		sf::Text* text_controls_;
		sf::Vector2f* screen_resolution_;
		sf::Clock game_clock_;
		Network* network_;

		struct StartMessage
		{
			bool player_team;			// What team the player will be on.
			float time;					// The current game time clock that both clients will base their lag offset from.
		};

		// Overloading packet operator functions.
		// Used for sending packet data.
		// This will allow me to send struct data through packets.
		friend sf::Packet& operator <<(sf::Packet& packet, const State::StartMessage& message)
		{
			return packet << message.player_team << message.time;
		}

		// This will allow me to receive struct data through packets.
		friend sf::Packet& operator >>(sf::Packet& packet, State::StartMessage& message)
		{
			return packet >> message.player_team >> message.time;
		}

};

#endif