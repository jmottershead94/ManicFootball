#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include "utilities.h"

class Connection : protected Utilities
{

	public:
		// Methods.
		Connection();
		~Connection();
		void Listen();
		bool Accept(sf::TcpSocket& client_socket);

		// Getters.
		// This will return our current connection listener for the server.
		inline sf::TcpListener& GetTCPListener() { return connection_listener_; }

	private:
		sf::TcpListener connection_listener_;	// The TCP listener for listening out for TCP connections.

};

#endif