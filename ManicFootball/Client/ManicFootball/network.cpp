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

	// Clearing the packet of any data.
	data_.clear();

	// If we have received data from the server.
	if (ReceivedData(data_))
	{
		// Check to see if it is okay to read the data.
		if (data_ >> starting_message)
		{
			// We have read some data from the starting message!
			// Get the current time, and the half round trip time from the server message.
			sf::Int32 lag = GetClock().getElapsedTime().asMilliseconds();
			sf::Int32 half_round_trip_time = (lag /2);
			
			// FOR TESTING.
			std::cout << "The lag client side is = " << lag << std::endl;
			std::cout << "The lag server side is = " << half_round_trip_time << std::endl;

			// Calculate the lag offset.
			// When we get a message from the server add on this time.
			lag_offset_ = lag - (starting_message.time + half_round_trip_time);

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

			// We could not read the starting message from the server.
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

	// If we have received any more data.
	if (ReceivedData(data_))
	{
		// Waiting for the second player to connect.
		bool ready = false;
		
		// Pass this time along with the message.
		SetTime();
		sf::Int32 current_time = GetTime().asMilliseconds() + lag_offset_;
		SetCurrentTime(current_time);

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

	// We have not received a ready flag from the server yet.
	return false;

}

void Network::SendInputMessageToServer(Input& client_input)
{
	
	// Clearing the packet of any data.
	data_.clear();

	// Placing client input into some data for transferring.
	data_ << client_input;

	// If we can successfully send the data.
	if (SendData(data_))
	{
		//std::cout << "Data has been sent to the server." << std::endl;
	}

}

bool Network::ReceivedInputMessageFromServer()
{

	// This is the struct that we will be passing the data into from the server.
	Input input;

	// Clearing the packet of any data.
	data_.clear();

	// If we have received data from the server.
	if (ReceivedData(data_))
	{
		// Check to see if it is okay to read the data.
		if (data_ >> input)
		{
			// Place the input data back into the packet data to be used by the client.
			data_ << input;

			// We have received some input data.
			return true;
		}
		// Otherwise, we could not read the data.
		else
		{
			// ERROR: The packet is not okay to read.
			DisplayErrorMessage(kDataReadingErrorMessage);

			// We could not read the input message.
			return false;
		}

		return false;
	}
	
	// We have not received any input yet.
	return false;

}

void Network::SendPositionMessageToServer(PositionUpdate& client_position)
{

	// Clearing the packet of any data.
	data_.clear();

	// Placing client input into some data for transferring.
	data_ << client_position;

	// If we can successfully send the data.
	if (SendData(data_))
	{
		//std::cout << "Data has been sent to the server." << std::endl;
	}

}

void Network::SendFinishMessageToServer(FinishMessage& client_finished)
{

	// Clearing the packet of any data.
	data_.clear();

	// Placing client input into some data for transferring.
	data_ << client_finished;

	// If we can successfully send the data.
	if (SendData(data_))
	{
		//std::cout << "Data has been sent to the server." << std::endl;
	}

}

bool Network::ReceivedFinishMessageFromServer()
{

	// This is the struct that we will be passing the data into from the server.
	FinishMessage finish_message;

	// Clearing the packet of any data.
	data_.clear();

	// If we have received data from the server.
	if (ReceivedData(data_))
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

		return false;
	}

	// We have not received any finish message data yet.
	return false;

}