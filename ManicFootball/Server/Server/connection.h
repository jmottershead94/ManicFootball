// Jason Mottershead, 1300455.

// Connection class header file.
// This class will provide the means for the client to connect to the server.

// Header guard.
#ifndef _CONNECTION_H_
#define _CONNECTION_H_

// Include files here.
#include "utilities.h"

// Connection IS A network utility, therefore inherits from it.
class Connection : protected Utilities
{

	public:
		// Methods.
		void Listen();
		bool Accept(sf::TcpSocket& client_socket);

		// Getters.
		// This will return our current connection listener for the server.
		inline sf::TcpListener& GetTCPListener()	{ return connection_listener_; }

	private:
		// Attributes.
		sf::TcpListener connection_listener_;		// The TCP listener for listening out for TCP connections.

};

#endif