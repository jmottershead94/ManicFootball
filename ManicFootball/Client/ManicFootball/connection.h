// Jason Mottershead, 1300455.

// Connection class header file.
// This class will provide the means for the client to connect to a server.

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
		Connection();
		~Connection();
		bool ToServer();

		// Getters.
		// This will return the current socket being used by the connection.
		inline sf::TcpSocket* GetSocket()	{ return socket_; }

	private:
		// Attributes.
		sf::TcpSocket* socket_;				// Our current socket for connecting to the server.

};

#endif