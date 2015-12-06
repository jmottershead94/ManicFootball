// Include header file here.
#include "network.h"

//////////////////////////////////////////////////////////
//======================================================//
//						Constructor						//
//======================================================//
// This will initialise any attributes, and start our	//
// server connection listener to listen out on port		//
// 5000.												//
//////////////////////////////////////////////////////////
Network::Network() : ready_(false),
	connected_clients_(0)
{

	// Make the connection listener listen out for connections on a specified port number.
	GetConnection().Listen();

}

//////////////////////////////////////////////////////////
//======================================================//
//						Destructor						//
//======================================================//
// This will remove all of the sockets from our			//
// network.												//
//////////////////////////////////////////////////////////
Network::~Network()
{

	// If there are sockets connected to the server.
	if (!sockets_.empty())
	{
		// Loop through all of the connections.
		for (auto& socket : sockets_)
		{
			// Disconnect the socket.
			socket->disconnect();

			// Delete the current socket and set it to null.
			delete socket;
			socket = nullptr;
		}
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//					AcceptConnection					//
//======================================================//
// This will place any connecting clients into a socket	//
// array, and then check if we have been able to accept	//
// a connection from that client.						//
//////////////////////////////////////////////////////////
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

	// If we have accepted a connection.
	if (GetConnection().Accept(client_socket))
	{
		// Clearing the packet of any data.
		data_.clear();

		// Send a starter message struct to player one.
		// Telling them what team they are on. (bool red_team = true).
		// Sending them the initial server timestamp for timing offsets on the client side.
		StartMessage starting_message;
		starting_message.player_team = team;								// Setting player one to be on the red team.
		starting_message.time = clock.getElapsedTime().asMilliseconds();	// Restarting the game clock for player one to determine lag offset.
		
		// Print out the current time server side.
		std::cout << "Starting message time is: " << starting_message.time << std::endl;

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
		// Otherwise, we could not send data to the client.
		else
		{
			// ERROR: A disconnection is taking place.
			DisplayErrorMessage(kConnectionErrorMessage);

			// Remove their socket from our connection.
			delete sockets_[connected_clients_];
			sockets_[connected_clients_] = nullptr;

			// Decrease the amount of connected clients we have.
			connected_clients_--;
		}
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//					ConnectionsAreReady					//
//======================================================//
// This will tell use if both of are connections are	//
// ready.												//
// We will see if both clients send back a ready flag,	//
// if not, we have an error.							//
//////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////
//======================================================//
//			ReceivedInputMessageFromClient				//
//======================================================//
// This will be our specific response for receiving an	//
// input message from the client.						//
// Here we will extract the input data from the packet,	//
// and then we can use the data for our level update.	//
//////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////
//======================================================//
//				SendInputMessageToClient				//
//======================================================//
// This will be our specific response for sending an	//
// input message to the server.							//
// We will place our input data into the packet, and	//
// then attempt to send the packet off to the client.	//
//////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////
//======================================================//
//			SendServerUpdateMessageToServer				//
//======================================================//
// This will be our specific response for sending a		//
// server update message to the clients.				//
// We will place our server update data into the		//
// packet, and then attempt to send the packet off to	//
// the server.											//
//////////////////////////////////////////////////////////
void Network::SendServerUpdateToClients(sf::TcpSocket& client_socket, ServerUpdate& client_position)
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