// Jason Mottershead, 1300455.

// Network class header file.
// This class will allow the server to establish connections and decided when to continue the game on.

// Header guard.
#ifndef _NETWORK_H_
#define _NETWORK_H_

// Include files here.
#include "utilities.h"
#include "connection.h"

class Network : public Utilities
{

	public:
		// Methods.
		Network();
		~Network();
		bool ConnectedToServer();
		bool ReceivedStartingMessage();
		bool ReceivedReadyMessage();

		// The structure for the game's starting message.
		struct StartMessage
		{
			bool player_team;			// What team the player will be on.
			float time;					// The current game time.
		};

		// Getters.
		// This will return the team that the client is on.
		inline bool GetAssignedTeam()		{ return team_; };

		// This will return the amount of lag that was calculate between the server and client.
		inline float GetLagOffset()			{ return lag_offset_; }

		// This will return the current connection that the network is using.
		inline Connection& GetConnection()	{ return connection_; }

	private:
		// Attributes.
		bool team_;
		float lag_offset_;
		sf::Packet data_;
		Connection connection_;

		// Methods.
		// Overloading packet operator functions.
		// Used for sending packet data.
		// This will allow me to send struct data through packets.
		friend sf::Packet& operator <<(sf::Packet& packet, const Network::StartMessage& message)
		{
			return packet << message.player_team << message.time;
		}

		// This will allow me to receive struct data through packets.
		friend sf::Packet& operator >>(sf::Packet& packet, Network::StartMessage& message)
		{
			return packet >> message.player_team >> message.time;
		}

};

#endif