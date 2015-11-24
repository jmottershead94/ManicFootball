#include "network_handler.h"

bool NetworkHandler::SendData(sf::Packet& data)
{

	// If we successfully sent the data to the server.
	if (connection_.GetSocket()->send(data) == sf::Socket::Done)
	{
		// Notify the client.
		return true;
	}

	// We can modify what the standard response for not sending a packet of data is here.
	// Without having to trawl through network sending code and modifying each if statement to provide a standard response.
	// ERROR: We could not send the data.
	DisplayErrorMessage(kDataSendingErrorMessage);

	// We could not send the data, notify the client.
	return false;

}

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

bool NetworkHandler::Disconnected()
{

	// Empty packet to see if our socket responds.
	sf::Packet check;

	// If a client wants to disconnect.
	if (connection_.GetSocket()->receive(check) == sf::Socket::Disconnected)
	{
		// Standard disconnection response here...
		DisplayErrorMessage(KDisconnectionErrorMessage);
		connection_.GetSocket()->disconnect();

		// A client has disconnected.
		return true;
	}

	// A client has not disconnected.
	return false;

}