#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#include <SFML\Network.hpp>

// The structure for the game's starting message.
// This will only be sent to both clients once they are connected to the server.
struct StartMessage
{
	bool player_team = false;		// What team the player will be on.
	float time = 0.0f;				// The current game time.
};

// The structure for the player's input.
// This will be the main message being sent across from the client to the server.
struct Input
{
	bool up = false;				// If the player is pressing up.
	bool right = false;				// If the player is pressing right.
	bool left = false;				// If the player is pressing left.
	float time = 0.0f;				// The current time that the input was given at.
};

// The structure for player's commands.
// This will be used to pass in the player class struct of commands.
struct Commands
{
	bool up = false;
	bool right = false;
	bool left = false;
};

// The structure for correcting dynamic object's positions.
// This will be sent every so often to make sure that objects are in the correct place.
struct PositionCorrection
{
	float x = 0.0f;					// The correct x position.
	float y = 0.0f;					// The correct y position.
	float time = 0.0f;				// The current time that the positions were given at.
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

// This will allow me to send Position Correction data through packets.
inline sf::Packet& operator <<(sf::Packet& packet, const PositionCorrection& message)	{ return packet << message.x << message.y << message.time; }

// This will allow me to receive Position Correction data through packets.
inline sf::Packet& operator >>(sf::Packet& packet, PositionCorrection& message)			{ return packet >> message.x >> message.y >> message.time; }

#endif