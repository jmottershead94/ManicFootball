#include "connection.h"

Connection::Connection()
{
}

Connection::~Connection()
{
}

void Connection::Listen()
{

	// Binding the listener to the port 5000.
	// Listen out for any connections on port 5000.
	if (connection_listener_.listen(kPort) != sf::Socket::Done)
	{
		// ERROR: for listening on the port number 5000; display error message.
		std::cout << kTCPListenerErrorMessage << std::endl;
		return;
	}

	// Telling the user what port the server is listening on.
	std::cout << "Server is listening to port " << kPort << ", waiting for connections..." << std::endl;

}

bool Connection::Accept(sf::TcpSocket& client_socket)
{

	// Checking to see if the client is able to connect to the server.
	if (connection_listener_.accept(client_socket) != sf::Socket::Done)
	{
		// ERROR: Could not accept a connection on the server.
		std::cout << kConnectionErrorMessage << std::endl;
		
		// We have not accepted the connection from this client.
		return false;
	}
	// Otherwise, the client has connected to the server.
	else
	{
		// We have accepted a connection from this client.
		return true;
	}

}