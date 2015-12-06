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
bool NetworkHandler::SendData(sf::TcpSocket& client_socket, sf::Packet& data)
{

	// If we successfully sent the data to the client.
	if (client_socket.send(data) == sf::Socket::Done)
	{
		// Notify the server.
		return true;
	}
	// Otherwise, if we have disconnected from the server.
	else if (client_socket.send(data) == sf::Socket::Disconnected)
	{
		DisplayErrorMessage(kConnectionErrorMessage);
		//client_socket.disconnect();
	}

	// We can modify what the standard response for not sending a packet of data is here.
	// Without having to trawl through network sending code and modifying each if statement to provide a standard response.
	// ERROR: We could not send the data.
	DisplayErrorMessage(kDataSendingErrorMessage);

	// We could not send the data, notify the server.
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