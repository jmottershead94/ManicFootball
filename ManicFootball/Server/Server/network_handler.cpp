#include "network_handler.h"

bool NetworkHandler::SendData(sf::TcpSocket& client_socket, sf::Packet& data)
{

	// If we successfully sent the data to the client.
	if (client_socket.send(data) == sf::Socket::Done)
	{
		// Notify the server.
		return true;
	}

	// We can modify what the standard response for not sending a packet of data is here.
	// Without having to trawl through network sending code and modifying each if statement to provide a standard response.
	// ERROR: We could not send the data.
	DisplayErrorMessage(kDataSendingErrorMessage);

	// We could not send the data, notify the server.
	return false;

}

bool NetworkHandler::ReceivedData(sf::TcpSocket& client_socket, sf::Packet& data)
{

	// If we have successfully received data from the client.
	if (client_socket.receive(data) == sf::Socket::Done)
	{
		// Notify the server.
		return true;
	}

	// We can modify what the standard response for not receiving a packet of data is here.
	// Without having to trawl through network receiving code and modifying each if statement to provide a standard response.
	// ERROR: We could not receive the data.
	DisplayErrorMessage(kDataReceivingErrorMessage);

	// We could not receive the data, notify the server.
	return false;
}