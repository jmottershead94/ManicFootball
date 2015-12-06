// Include header file here.
#include "network_handler.h"

//////////////////////////////////////////////////////////
//======================================================//
//						SendData						//
//======================================================//
// This will be the standard response for sending data.	//
// This function will return true if we are able to		//
// send a packet.										//
//////////////////////////////////////////////////////////
bool NetworkHandler::SendData(sf::Packet& data)
{

	// If we successfully sent the data to the server.
	if (connection_.GetSocket()->send(data) == sf::Socket::Done)
	{
		// Notify the client.
		return true;
	}
	// Otherwise, if we have disconnected from the server.
	else if (connection_.GetSocket()->send(data) == sf::Socket::Disconnected)
	{
		// ERROR: We could not connect to the server.
		DisplayErrorMessage(kConnectionErrorMessage);

		// Disconnect from the server.
		//connection_.GetSocket()->disconnect();
	}

	// We can modify what the standard response for not sending a packet of data is here.
	// Without having to trawl through network sending code and modifying each if statement to provide a standard response.
	// ERROR: We could not send the data.
	DisplayErrorMessage(kDataSendingErrorMessage);

	// We could not send the data, notify the client.
	return false;

}

//////////////////////////////////////////////////////////
//======================================================//
//					ReceivedData						//
//======================================================//
// This will be the standard response for receiving		//
// data. This function will return true if we are able	//
// to receive a packet.									//
//////////////////////////////////////////////////////////
bool NetworkHandler::ReceivedData(sf::Packet& data)
{

	// If we have successfully received data from the server.
	if (connection_.GetSocket()->receive(data) == sf::Socket::Done)
	{
		// Notify the client.
		return true;
	}

	// We can modify what the standard response for not receiving a packet of data is here.
	// Without having to trawl through network receiving code and modifying each if statement to provide a standard response.
	// ERROR: We could not receive the data.
	DisplayErrorMessage(kDataReceivingErrorMessage);

	// We could not receive the data, notify the client.
	return false;
}