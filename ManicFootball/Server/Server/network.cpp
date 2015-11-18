// Include header file here.
#include "network.h"

Network::Network() : connected_clients_(0),
	ready_(false)
{

	// Make the connection listener listen out for connections on a specified port number.
	GetConnection().Listen();

}

Network::~Network()
{

	// If there are sockets connected to the server.
	if (!sockets_.empty())
	{
		// Loop through all of the connections.
		for (auto& socket : sockets_)
		{
			// Delete the current socket and set it to null.
			delete socket;
			socket = nullptr;
		}
	}

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

	if (GetConnection().Accept(client_socket))
	{
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

		// If we can send the data over to the client.
		if (SendData(client_socket, data_))
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
	if (SendData(*sockets_[0], data_) && SendData(*sockets_[1], data_))
	{
		// Let the game continue.
		return true;
	}

	// ERROR: The data could not be sent!
	DisplayErrorMessage(kDataSendingErrorMessage);

	// Don't let the game continue.
	return false;

}