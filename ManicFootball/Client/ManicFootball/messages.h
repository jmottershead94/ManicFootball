// Jason Mottershead, 1300455.

// Messages header file.
// This header file will provide a base set of structs that every file can use to pass messages
// between the client and the server.

// Header guard.
#ifndef _MESSAGES_H_
#define _MESSAGES_H_

// Include files here.
#include <SFML\Network.hpp>

// The structure for the game's starting message.
// This will only be sent to both clients once they are connected to the server.
struct StartMessage
{
	bool player_team = false;		// What team the player will be on.
	sf::Int32 time = 0;				// The current game time.
};

// The structure for the player's input.
// This will be the main message being sent across from the client to the server.
struct Input
{
	bool up = false;				// If the player is pressing up.
	bool right = false;				// If the player is pressing right.
	bool left = false;				// If the player is pressing left.
	sf::Int32 time = 0;				// The current time that the input was given at.
};

// The struct for updating the dynamic object positions.
// This will be sent to the clients every frame, will be used for interpolation.
struct ServerUpdate
{
	float x = 0.0f;					// The current x position.
	float y = 0.0f;					// The current y position.
	int id = 0;						// The current id number.
	int red_score = 0;				// The current red team score.
	int blue_score = 0;				// The current blue team score.
	sf::Int32 time = 0;				// The current time that the server update was given at.
};

// Overloading packet operator functions.
// Used for sending packet data.
// This will allow me to send Start Message data through packets.
inline sf::Packet& operator <<(sf::Packet& packet, const StartMessage& message)			{ return packet << message.player_team << message.time; }

// This will allow me to receive Start Message data through packets.
inline sf::Packet& operator >>(sf::Packet& packet, StartMessage& message)				{ return packet >> message.player_team >> message.time; }

// This will allow me to send Input data through packets.
inline sf::Packet& operator <<(sf::Packet& packet, const Input& message)				{ return packet << message.up << message.right << message.left << message.time; }

// This will allow me to receive Input data through packets.
inline sf::Packet& operator >>(sf::Packet& packet, Input& message)						{ return packet >> message.up >> message.right >> message.left >> message.time; }

// This will allow me to send Server Update data through packets.
inline sf::Packet& operator <<(sf::Packet& packet, const ServerUpdate& message)		{ return packet << message.x << message.y << message.id << message.red_score << message.blue_score << message.time; }

// This will allow me to receive Server Update data through packets.
inline sf::Packet& operator >>(sf::Packet& packet, ServerUpdate& message)				{ return packet >> message.x >> message.y >> message.id >> message.red_score >> message.blue_score >> message.time; }

#endif