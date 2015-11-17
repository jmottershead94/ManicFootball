// Jason Mottershead, 1300455.

// Network class header file.
// This class will allow the server to establish connections and decided when to continue the game on.

// Header guard.
#ifndef _NETWORK_H_
#define _NETWORK_H_

// Include files here.
#include <iostream>
#include <array>
#include <SFML/Network.hpp>

class Network
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
		inline bool GetAssignedTeam()	{ return team_; };

		// This will return the amount of lag that was calculate between the server and client.
		inline float GetLagOffset()		{ return lag_offset_; }

	private:
		// Attributes.
		const unsigned short kPort = 5000;
		const std::string kIPAddress = "127.0.0.1";
		const std::string kTCPListenerErrorMessage = "ERROR: TCP connection listener failed.";	// The error message if tcp connection messes up.
		const std::string kConnectionErrorMessage = "ERROR: Client could not connect.";			// The error message if the client cannot connect.
		const std::string kDataSendingErrorMessage = "ERROR: Data could not be sent.";			// The error message if the SFML packets cannot send.
		const std::string kDataReceivingErrorMessage = "ERROR: Data could not be received.";	// The error message if the SFML packets cannot be received.
		const std::string kDataReadingErrorMessage = "ERROR: Data could not be read.";			// The error message if the SFML packets cannot be read.
		bool team_;
		float lag_offset_;
		sf::TcpSocket* socket_;
		sf::Packet data_;
		sf::Clock lag_offset_clock_;	// This will be used to work out the lag offset from the server.

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