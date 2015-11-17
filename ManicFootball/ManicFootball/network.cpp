#include "network.h"

Network::Network()
{

	// Initialising a new socket.
	socket_ = new sf::TcpSocket();

}

Network::~Network()
{
}

bool Network::ConnectedToServer()
{

	// Use the created socket and connect to 127.0.0.1 (this machine) on port 5000, and use the default time out for this machine.
	sf::Socket::Status status = socket_->connect(kIPAddress, kPort);

	// If the socket has not connected to the server.
	if (status != sf::Socket::Done)
	{
		// ERROR: Could not connect to the server.
		std::cout << kConnectionErrorMessage << std::endl;

		// The client has not connected to the server.
		return false;
	}
	// Otherwise, if the socket does connect to the server.
	else
	{
		// Start the lag timer.
		lag_offset_clock_.restart().asMilliseconds();

		// Tell the user what IP address they have connected to.
		std::cout << "Connected to the server: " << kIPAddress << std::endl;

		// The client has connected to the server.
		return true;
	}

	// The client has not connected to the server.
	return false;

}

bool Network::ReceivedStartingMessage()
{

	// This is the struct that we will be passing the data into from the server.
	StartMessage starting_message;

	// Clearing the packer of any data.
	data_.clear();

	// If the socket did not receive any data.
	if (socket_->receive(data_) != sf::Socket::Done)
	{
		// We were unable to read some data from the starting message.
		std::cout << kDataReceivingErrorMessage << std::endl;

		// We have not received a starting message from the server.
		return false;
	}
	// Otherwise, we were able to receive the data.
	else
	{
		// Check to see if it is okay to read the data.
		if (data_ >> starting_message)
		{
			// We have read some data from the starting message!
			// Get the current time, and the half round trip time from the server message.
			float half_round_trip_time = (starting_message.time * 0.5f);
			float lag = lag_offset_clock_.getElapsedTime().asMilliseconds();

			// FOR TESTING.
			std::cout << "The lag client side is = " << lag << std::endl;
			std::cout << "The lag server side is = " << half_round_trip_time << std::endl;

			// Calculate the lag offset.
			lag_offset_ = half_round_trip_time - lag;

			// FOR TESTING.
			std::cout << "The lag offset is = " << lag_offset_ << std::endl;

			// Store what team the player will be on.
			team_ = starting_message.player_team;

			// We have successfully received a starting message from the server.
			return true;
		}
		// Otherwise, we could not read the data.
		else
		{
			// ERROR: The packet is not okay to read.
			std::cout << kDataReadingErrorMessage << std::endl;

			// We have not received a starting message from the server.
			return false;
		}
	}

	// We have not received a starting message from the server.
	return false;

}

bool Network::ReceivedReadyMessage()
{

	// Clearing the packet of any data.
	data_.clear();

	// Wait for the second player to connect.
	if (socket_->receive(data_) != sf::Socket::Done)
	{
		// We were unable to read some data from the starting message.
		std::cout << kDataReceivingErrorMessage << std::endl;

		// We have not received a ready flag from the server yet.
		return false;
	}
	else
	{
		bool ready = false;

		// Check to see if it is okay to read the data.
		if (data_ >> ready)
		{
			// We have successfully read the ready message.
			return true;
		}
		// Otherwise, the data is not okay to read.
		else
		{
			// ERROR: The packet is not okay to read.
			std::cout << kDataReadingErrorMessage << std::endl;

			// We have not been able to read the ready flag from the server.
			return false;
		}

		// We have not been able to read the ready flag from the server.
		return false;
	}

	// We have not received a ready flag from the server yet.
	return false;

}