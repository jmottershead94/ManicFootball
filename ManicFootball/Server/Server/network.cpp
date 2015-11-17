#include "network.h"

Network::Network() : connected_clients_(0),
	ready_(false)
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

Network::~Network()
{
}

void Network::AcceptConnection(sf::TcpSocket& client_socket, bool team, sf::Clock& clock)
{
	
	// If the array index incrementer is less than the size of the array.
	if (connected_clients_ < sockets_.size())
	{
		// Place the client sockets into the sockets array.
		sockets_[connected_clients_] = &client_socket;

		// Incrementing the sockets counter.
		// So that we place the next socket in the next element along.
		connected_clients_++;
	}

	// Checking to see if the client is able to connect to the server.
	if (connection_listener_.accept(client_socket) != sf::Socket::Done)
	{
		// ERROR: Could not accept a connection on the server.
		std::cout << kConnectionErrorMessage << std::endl;
		return;
	}
	// Otherwise, the client has connected to the server.
	else
	{
		// Print out the IP address of the connecting client.
		std::cout << "Client connected: " << client_socket.getRemoteAddress() << std::endl;
		
		// Clearing the packet of any data.
		data_.clear();

		// Send a starter message struct to player one.
		// Telling them what team they are on. (bool red_team = true).
		// Sending them the initial server timestamp for timing offsets on the client side.
		StartMessage starting_message;
		starting_message.player_team = team;							// Setting player one to be on the red team.
		starting_message.time = clock.restart().asMilliseconds();		// Restarting the game clock for player one to determine lag offset.

		// Placing the starting message into the data packet for sending.
		data_ << starting_message;

		// If the data could not be sent back to the client.
		if (client_socket.send(data_) != sf::Socket::Done)
		{
			// ERROR: The data could not be sent.
			std::cout << kDataSendingErrorMessage << std::endl;
			return;
		}
		// Otherwise, the data was sent successfully.
		else
		{
			// Check the current number of connections we have.
			// If we have 2 elements in our sockets array.
			if (connected_clients_ == 1)
			{
				// We have two players!
				ready_ = true;
			}
		}
	}

}

bool Network::ConnectionsAreReady()
{

	// Clearing the packet of any data.
	data_.clear();

	// Telling all connected players that the game is ready to start.
	data_ << ready_;
	
	// Checking to see if both sockets have received the ready flag.
	// If they have not received the ready flag.
	if ((sockets_[0]->send(data_) != sf::Socket::Done) || (sockets_[1]->send(data_) != sf::Socket::Done))
	{
		// ERROR: The data could not be sent!
		std::cout << kDataSendingErrorMessage << std::endl;
		return false;
	}
	// Otherwise, both clients have received the ready flag.
	else if ((sockets_[0]->send(data_) == sf::Socket::Done) && (sockets_[1]->send(data_) == sf::Socket::Done))
	{
		// Let the game continue.
		return true;
	}

	// Don't let the game continue.
	return false;

}