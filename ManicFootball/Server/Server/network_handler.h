// Jason Mottershead, 1300455.

// Network Handler class header file.
// This class will provide all of the basic functionality for the network.
// As well as provide common network methods, structures and attributes.

// Header guard.
#ifndef _NETWORK_HANDLER_H_
#define _NETWORK_HANDLER_H_

// Include files here.
#include "messages.h"
#include "utilities.h"
#include "connection.h"

// Network handler IS A network utility, therefore inherits from it.
class NetworkHandler : protected Utilities
{

	public:
		// Methods.
		bool SendData(sf::TcpSocket& client_socket, sf::Packet& data);
		bool ReceivedData(sf::TcpSocket& client_socket, sf::Packet& data);
		bool DisconnectingClients(sf::TcpSocket& client_socket);

		// Setters.
		// Set the current time value for the client.
		inline void SetCurrentTime(sf::Int32& current_time)	{ current_time_ = current_time; }

		// Getters.
		// This will return the current connection we are using to handle the network connections.
		inline Connection& GetConnection()	{ return connection_; }
		
		// This will return the current time value for the client.
		inline sf::Int32& GetCurrentTime()  { return current_time_; }

	private:
		// Attributes.
		Connection connection_;
		sf::Int32 current_time_;

};

#endif