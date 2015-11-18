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
		DisplayErrorMessage(kTCPListenerErrorMessage);
		return;
	}

	// Telling the user what port the server is listening on.
	std::cout << "Server is listening to port " << kPort << ", waiting for connections..." << std::endl;

}

bool Connection::Accept(sf::TcpSocket& client_socket)
{

	// If we have successfully accepted a connection from the client.
	if (connection_listener_.accept(client_socket) == sf::Socket::Done)
	{
		// Print out the IP address of the connecting client.
		std::cout << "Client connected from: " << client_socket.getRemoteAddress() << std::endl;

		// We have accepted a connection from this client, notify the server.
		return true;
	}

	// We can modify what the standard response for not connecting with a client is here.
	// Without having to go through network connecting code and modifying each if statement to provide a standard response.
	// ERROR: Could not accept a connection on the server.
	DisplayErrorMessage(kConnectionErrorMessage);

	// We have not accepted the connection from this client.
	return false;

}