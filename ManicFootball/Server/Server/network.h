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
#include "network_handler.h"

// The maximum number of players that we want in the game.
#define MAX_NUMBER_OF_CONNECTIONS 2

// Network IS A handled network, therefore inherits from it.
class Network : public NetworkHandler
{

	public:
		// Methods.
		Network();
		~Network();
		void AcceptConnection(sf::TcpSocket& client_socket, bool team, sf::Clock& clock);
		bool ConnectionsAreReady();

		// The structure for the game's starting message.
		//struct StartMessage
		//{
		//	bool player_team;			// What team the player will be on.
		//	float time;					// The current game time.
		//};

		// Getters.
		// This will return the current number of clients in the network.
		inline int GetNumberOfConnectedClients()	{ return connected_clients_; }

		// This will return whether or not the server has all of the connections it can have.
		inline bool IsReady()						{ return ready_; }

	private:
		// Attributes.
		
		//const unsigned short kPort = 5000;														// The port number we would like the server to listen for connections on.
		//const std::string kIPAddress = "127.0.0.1";												// The IP address we are working with.
		//const std::string kTCPListenerErrorMessage = "ERROR: TCP connection listener failed.";	// The error message if tcp connection messes up.
		//const std::string kConnectionErrorMessage = "ERROR: Client could not connect.";			// The error message if the client cannot connect.
		//const std::string kDataSendingErrorMessage = "ERROR: Data could not be sent.";			// The error message if the SFML packets cannot send.
		bool ready_;																			// Whether the server is ready to start the level or not.
		int connected_clients_;																	// The current number of connected clients to this server.
		std::array< sf::TcpSocket*, MAX_NUMBER_OF_CONNECTIONS > sockets_;						// A data structure holding all of the connected client's TCP sockets.
		sf::Packet data_;																		// Packet data used to store and pass along messages.
		//sf::TcpListener connection_listener_;													// The TCP listener for listening out for TCP connections.

		//// Methods.
		//// Overloading packet operator functions.
		//// Used for sending packet data.		
		//// This will allow me to send Start Message struct data through packets.
		//inline friend sf::Packet& operator <<(sf::Packet& packet, const Network::StartMessage& message) { return packet << message.player_team << message.time; }

		//// Used for receiving packet data.
		//// This will allow me to receive Start Message struct data through packets.
		//inline friend sf::Packet& operator >>(sf::Packet& packet, Network::StartMessage& message)		{ return packet >> message.player_team >> message.time; }

};

#endif