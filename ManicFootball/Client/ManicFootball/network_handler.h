// Jason Mottershead, 1300455.

// Network Handler class header file.
// This class will provide all of the basic functionality for the network.
// As well as provide common network methods, structures and attributes.

// Header guard.
#ifndef _NETWORK_HANDLER_H_
#define _NETWORK_HANDLER_H_

// Include files here.
#include "messages.h"
#include "utilities.h"
#include "connection.h"

// Network handler IS A network utility, therefore inherits from it.
class NetworkHandler : protected Utilities
{

	public:
		// Methods.
		bool SendData(sf::Packet& data);
		bool ReceivedData(sf::Packet& data);
		bool Disconnected();

		// Setters.
		// Set the current time value for the client.
		inline void SetCurrentTime(sf::Int32& current_time)	{ current_time_ = current_time; }

		// Getters.
		// This will return the current connection that the network is using.
		inline Connection& GetConnection()	{ return connection_; }

		// This will return the current clock.
		inline sf::Clock& GetClock()		{ return game_clock_; }
	
		// This will return the current time value for the client.
		inline sf::Int32& GetCurrentTime()  { return current_time_; }

		// Pure virtual methods.
		// Every network for a game using this "framework" must have these functions implemented.
		virtual bool ReceivedStartingMessage() = 0;
		virtual bool ReceivedReadyMessage() = 0;
		virtual void SendInputMessageToServer(Input& client_input) = 0;

	private:
		// Attributes.
		Connection connection_;
		sf::Time game_time_;
		sf::Int32 current_time_;

};

#endif