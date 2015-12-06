// Jason Mottershead, 1300455.

// Network class header file.
// This class will allow the server to establish connections and decided when to continue the game on.

// Header guard.
#ifndef _NETWORK_H_
#define _NETWORK_H_

// Include files here.
#include "network_handler.h"

// Network IS A handled network, therefore inherits from it.
class Network : public NetworkHandler
{

	public:
		// Methods.
		bool ReceivedStartingMessage();
		bool ReceivedReadyMessage();
		void SendInputMessageToServer(Input& client_input);
		bool ReceivedInputMessageFromServer();
		bool ReceivedServerUpdateMessageFromServer();

		// Getters.
		// This will return the current threshold for interpolation to obey.
		inline const float& GetThreshold()	{ return kThreshold; }

		// This will return the team that the client is on.
		inline bool& GetAssignedTeam()		{ return team_; };

		// This will return the amount of lag that was calculate between the server and client.
		inline sf::Int32& GetLagOffset()	{ return lag_offset_; }
		
		// This will return the current set of data.
		inline sf::Packet& GetData()		{ return data_; }

	private:
		// Attributes.
		const float kThreshold = 15.0f;		// The current position threshold for our network. We will check this for position differences.
		bool team_;							// What team we have been assigned to.
		sf::Int32 lag_offset_;				// The lag offset for the 3-way handshake to be completed.
		sf::Packet data_;					// The packet of data we are sending and receiving from.

};

#endif