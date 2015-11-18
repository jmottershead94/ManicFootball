#include "network.h"

Network::Network()
{
}

Network::~Network()
{
}

bool Network::ReceivedStartingMessage()
{

	// This is the struct that we will be passing the data into from the server.
	StartMessage starting_message;

	// Clearing the packer of any data.
	data_.clear();

	// If we have received data from the server.
	if (ReceivedData(data_))
	{
		// Check to see if it is okay to read the data.
		if (data_ >> starting_message)
		{
			// We have read some data from the starting message!
			// Get the current time, and the half round trip time from the server message.
			//////////////////////////////////////////////////////////////////////////////////
			// Conversion from float to sf::Int32 may be causing strange lag offset result...
			sf::Int32 half_round_trip_time = (starting_message.time * 0.5f);
			sf::Int32 lag = lag_offset_clock_.getElapsedTime().asMilliseconds();
			//////////////////////////////////////////////////////////////////////////////////

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
			DisplayErrorMessage(kDataReadingErrorMessage);

			// We have not received a starting message from the server.
			return false;
		}
	}

	// ERROR: We were unable to read some data from the starting message.
	DisplayErrorMessage(kDataReceivingErrorMessage);

	// We have not received a starting message from the server.
	return false;

}

bool Network::ReceivedReadyMessage()
{

	// Clearing the packet of any data.
	data_.clear();

	// If we have received any more data.
	if (ReceivedData(data_))
	{
		// Waiting for the second player to connect.
		bool ready = false;

		// Check to see if it is okay to read the data.
		if (data_ >> ready)
		{
			// We have successfully read the ready message.
			return ready;
		}
		// Otherwise, the data is not okay to read.
		else
		{
			// ERROR: The packet is not okay to read.
			DisplayErrorMessage(kDataReadingErrorMessage);

			// We have not been able to read the ready flag from the server.
			return ready;
		}
	}

	// ERROR: We were unable to receive some data from the starting message.
	DisplayErrorMessage(kDataReceivingErrorMessage);

	// We have not received a ready flag from the server yet.
	return false;

}

void Network::SendInputMessageToServer(Commands& commands, float time)
{
	
	// Clearing the packet of any data.
	data_.clear();

	// Creating an instance on input.
	// Placing all of the data from the level into the network struct for sending.
	Input client_input;
	client_input.up = commands.up;
	client_input.right = commands.right;
	client_input.left = commands.left;
	client_input.time = time;

	// Placing client input into some data for transferring.
	data_ << client_input;

	// If we can successfully send the data.
	if (SendData(data_))
	{
		// We have successfully sent the input message to the server.
		// TESTING.
		std::cout << "Up Command = " + client_input.up << std::endl;
	}

}