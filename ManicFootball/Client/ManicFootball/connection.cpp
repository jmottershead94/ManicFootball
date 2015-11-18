#include "connection.h"

Connection::Connection()
{

	// Initialising a new TCP socket.
	socket_ = new sf::TcpSocket();

}

Connection::~Connection()
{
}

// This will tell us whether or not the client has connected to the server yet.
bool Connection::ToServer()
{

	// Use the created socket and connect to 127.0.0.1 (this machine) on port 5000, and use the default time out for this machine.
	sf::Socket::Status status = socket_->connect(kIPAddress, kPort);

	// If the socket has not connected to the server.
	if (status != sf::Socket::Done)
	{
		// ERROR: Could not connect to the server.
		DisplayErrorMessage(kConnectionErrorMessage);

		// The client has not connected to the server.
		return false;
	}
	// Otherwise, if the socket does connect to the server.
	else
	{
		// Tell the user what IP address they have connected to.
		std::cout << "Connected to the server: " << kIPAddress << std::endl;

		// Start the lag timer.
		lag_offset_clock_.restart().asMilliseconds();

		// The client has connected to the server.
		return true;
	}

	// The client has not connected to the server.
	return false;

}