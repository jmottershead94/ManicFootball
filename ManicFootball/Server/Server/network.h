#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <array>
#include <SFML/Network.hpp>

// The maximum number of players that we want in the game.
#define MAX_NUMBER_OF_CONNECTIONS 2

class Network
{

	public:
		// Methods
		Network();
		~Network();
		void AcceptConnection(sf::TcpSocket& client_socket, bool team, sf::Clock& clock);
		bool ConnectionsAreReady();

		// The structure for the game's starting message.
		struct StartMessage
		{
			bool player_team;			// What team the player will be on.
			float time;					// The current game time.
		};

		// Getters.
		// This will return the current number of clients in the network.
		inline int GetNumberOfConnectedClients() { return connected_clients_; }

		// This will return whether or not there are 
		inline bool IsReady() { return ready_; }

	protected:
		// Attributes.
		const unsigned short kPort = 5000;
		const std::string kIPAddress = "127.0.0.1";
		const std::string kTCPListenerErrorMessage = "ERROR: TCP connection listener failed.";
		const std::string kConnectionErrorMessage = "ERROR: Client could not connect.";
		const std::string kDataSendingErrorMessage = "ERROR: Data could not be sent.";
		bool ready_;
		std::array< sf::TcpSocket*, MAX_NUMBER_OF_CONNECTIONS > sockets_;
		sf::Packet data_;
		sf::TcpSocket* socket_;
		sf::TcpListener connection_listener_;

		// Methods.
		// Overloading packet operator functions.
		// Used for sending packet data.		
		// This will allow me to send struct data through packets.
		inline friend sf::Packet& operator <<(sf::Packet& packet, const Network::StartMessage& message) { return packet << message.player_team << message.time; }

		// Used for receiving packet data.
		// This will allow me to receive struct data through packets.
		inline friend sf::Packet& operator >>(sf::Packet& packet, Network::StartMessage& message)		{ return packet >> message.player_team >> message.time; }

	private:
		int connected_clients_;
};

#endif