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
		starting_message.player_team = team;						// Setting player one to be on the red team.
		starting_message.time = clock.getElapsedTime().asMilliseconds();	// Restarting the game clock for player one to determine lag offset.
		
		// Print out the current time server side.
		std::cout << "Starting message time is: " << starting_message.time << std::endl;

		// Placing the starting message into the data packet for sending.
		data_ << starting_message;

		std::cout << "Starting message time is: " << starting_message.time << std::endl;

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

bool Network::ReceivedInputMessageFromClient(sf::TcpSocket& client_socket)
{

	// Creating the struct that will hold our input data from the client.
	Input client_input;
	
	// Clearing the packet of any data.
	data_.clear();

	// If we have received any data from any of the sockets.
	if (ReceivedData(client_socket, data_))
	{
		// Check to see if it is okay to read the data.
		if (data_ >> client_input)
		{
			// If it is, place the current client input data back into the packet.
			data_ << client_input;

			// Apply input to the level objects.
			return true;
		}
		// Otherwise, we could not read the data.
		else
		{
			// ERROR: The packet is not okay to read.
			DisplayErrorMessage(kDataReadingErrorMessage);

			// We could not read the input message from the client.
			return false;
		}
	}

	// ERROR: We were unable to read some data from the starting message.
	DisplayErrorMessage(kDataReceivingErrorMessage);

	return false;

}

void Network::SendInputToClients(sf::TcpSocket& client_socket, Input& client_input)
{

	// Clearing the packet of any data.
	data_.clear();

	// Placing the starting message into the data packet for sending.
	data_ << client_input;

	// If we can send the data over to the client.
	if (SendData(client_socket, data_))
	{
		// We have sent the data!
	}

}

void Network::SendDeadReckoningToClients(sf::TcpSocket& client_socket, PositionUpdate& client_position)
{

	// Clearing the packet of any data.
	data_.clear();

	// Placing the starting message into the data packet for sending.
	data_ << client_position;

	// If we can send the data over to the client.
	if (SendData(client_socket, data_))
	{
		// We have sent the data!
	}

}

bool Network::ReceivedPositionMessageFromClient()
{

	// Creating the struct that will hold our input data from the client.
	PositionUpdate client_position;

	// Clearing the packet of any data.
	data_.clear();

	// Looping through all of the sockets that we currently have.
	for (auto& socket : sockets_)
	{
		// If we have received any data from any of the sockets.
		if (ReceivedData(*socket, data_))
		{
			// Check to see if it is okay to read the data.
			if (data_ >> client_position)
			{
				// Place the data back into the packet.
				data_ << client_position;

				// Apply input to the level objects.
				return true;
			}
			// Otherwise, we could not read the data.
			else
			{
				// ERROR: The packet is not okay to read.
				DisplayErrorMessage(kDataReadingErrorMessage);

				// We could not read the input message from the client.
				return false;
			}
		}
	}

	// ERROR: We were unable to read some data from the starting message.
	DisplayErrorMessage(kDataReceivingErrorMessage);

	return false;

}

bool Network::ReceivedFinishMessageFromClients(sf::TcpSocket& client_socket)
{

	// This is the struct that we will be passing the data into from the server.
	FinishMessage finish_message;

	// Clearing the packet of any data.
	data_.clear();

	// If we have received data from the server.
	if (ReceivedData(client_socket, data_))
	{
		// Check to see if it is okay to read the data.
		if (data_ >> finish_message)
		{
			// Place the input data back into the packet data to be used by the client.
			data_ << finish_message;

			// We have received some finish message data.
			return true;
		}
		// Otherwise, we could not read the data.
		else
		{
			// ERROR: The packet is not okay to read.
			DisplayErrorMessage(kDataReadingErrorMessage);

			// We could not read the finish message data.
			return false;
		}
	}

	// We have not received any finish message data yet.
	return false;

}

void Network::SendFinishMessageToClients(sf::TcpSocket& client_socket, FinishMessage& client_finished)
{

	// Clearing the packet of any data.
	data_.clear();

	// Placing the starting message into the data packet for sending.
	data_ << client_finished;

	// If we can send the data over to the client.
	if (SendData(client_socket, data_))
	{
		// We have sent the data!
	}

}