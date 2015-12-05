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
		bool ReceivedInputMessageFromClient(sf::TcpSocket& client_socket);
		void SendInputToClients(sf::TcpSocket& client_socket, Input& client_input);
		void SendDeadReckoningToClients(sf::TcpSocket& client_socket, PositionUpdate& client_position);
		//void SendPositionCorrectionToClients(sf::TcpSocket& client_socket, PositionCorrection& server_positions);
		bool ReceivedPositionMessageFromClient();
		bool ReceivedFinishMessageFromClients(sf::TcpSocket& client_socket);
		void SendFinishMessageToClients(sf::TcpSocket& client_socket, FinishMessage& client_finished);
		
		// Getters.
		// This will return the current number of clients in the network.
		inline unsigned int GetNumberOfConnectedClients()								{ return connected_clients_; }

		// This will return whether or not the server has all of the connections it can have.
		inline bool IsReady()															{ return ready_; }

		// This will return all of the sockets that we have.
		inline std::array<sf::TcpSocket*, MAX_NUMBER_OF_CONNECTIONS> GetClientSockets() { return sockets_; }

		// This will return the current data that we can have access to.
		inline sf::Packet& GetData()													{ return data_; }

	private:
		// Attributes.
		bool ready_;																			// Whether the server is ready to start the level or not.
		unsigned int connected_clients_;														// The current number of connected clients to this server.
		std::array< sf::TcpSocket*, MAX_NUMBER_OF_CONNECTIONS > sockets_;						// A data structure holding all of the connected client's TCP sockets.
		sf::Packet data_;																		// Packet data used to store and pass along messages.
		
		
};

#endif