// Include header file here.
#include "network.h"

//////////////////////////////////////////////////////////
//======================================================//
//				ReceivedStartingMessage					//
//======================================================//
// This will be our specific response for receiving a	//
// starting message from the server.					//
// Here we will find out what team we have been			//
// assigned, and calculate the lag offset.				//
//////////////////////////////////////////////////////////
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
			
			// Output the current lag statistics to the client.
			std::cout << "The lag client side is = " << lag << std::endl;
			std::cout << "The lag server side is = " << half_round_trip_time << std::endl;

			// Calculate the lag offset.
			// When we get a message from the server add on this time.
			lag_offset_ = abs(lag - (starting_message.time + half_round_trip_time));

			// Output the current 3-way handshake lag offset to the client.
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

//////////////////////////////////////////////////////////
//======================================================//
//				ReceivedReadyMessage					//
//======================================================//
// This will be our specific response for receiving a	//
// ready message from the server.						//
// This will notify us when there is another player		//
// that has connected to the server.					//
//////////////////////////////////////////////////////////
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
		sf::Int32 current_time = GetClock().getElapsedTime().asMilliseconds() + lag_offset_;
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

//////////////////////////////////////////////////////////
//======================================================//
//				SendInputMessageToServer				//
//======================================================//
// This will be our specific response for sending an	//
// input message to the server.							//
// We will place our input data into the packet, and	//
// then attempt to send the packet off to the server.	//
//////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////
//======================================================//
//			ReceivedInputMessageFromServer				//
//======================================================//
// This will be our specific response for receiving an	//
// input message from the server.						//
// Here we will extract the input data from the packet,	//
// and then we can use the data for our level update.	//
//////////////////////////////////////////////////////////
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
			// Pass this time along with the message.
			sf::Int32 current_time = GetClock().getElapsedTime().asMilliseconds() + lag_offset_;
			SetCurrentTime(current_time);

			// Add on the offset gathered from the trip to the server.
			input.time = GetCurrentTime();

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

//////////////////////////////////////////////////////////
//======================================================//
//			ReceivedServerUpdateMessageFromServer		//
//======================================================//
// This will be our specific response for receiving a	//
// server update message from the server.				//
// Here we will extract the server update data from the	//
// packet, and then we can use the data for our level	//
// update.												//
//////////////////////////////////////////////////////////
bool Network::ReceivedServerUpdateMessageFromServer()
{

	// This is the struct that we will be passing the data into from the server.
	ServerUpdate position_update;

	// Clearing the packet of any data.
	data_.clear();

	// If we have received data from the server.
	if (ReceivedData(data_))
	{
		// Check to see if it is okay to read the data.
		if (data_ >> position_update)
		{
			// Pass this time along with the message.
			sf::Int32 current_time = GetClock().getElapsedTime().asMilliseconds() + lag_offset_;
			SetCurrentTime(current_time);

			// Add on the offset gathered from the trip to the server.
			position_update.time = GetCurrentTime();

			// Place the input data back into the packet data to be used by the client.
			data_ << position_update;

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