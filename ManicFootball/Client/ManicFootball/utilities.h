// Jason Mottershead, 1300455.

// Utilities class header file.
// This class will provide basic attributes used for both server and client.

// Header guard.
#ifndef _UTILITIES_H_
#define _UTILITIES_H_

// Include files here.
#include <iostream>
#include <SFML/Network.hpp>

class Utilities
{

	protected:
		// Attributes.
		const unsigned short kPort = 5000;
		const std::string kIPAddress = "127.0.0.1";
		const std::string kTCPListenerErrorMessage = "ERROR: TCP connection listener failed.";	// The error message if tcp connection messes up.
		const std::string kConnectionErrorMessage = "ERROR: Client could not connect.";			// The error message if the client cannot connect.
		const std::string KDisconnectionErrorMessage = "ERROR: Client has disconnected.";		// The error message if a client disconnects.
		const std::string kDataSendingErrorMessage = "ERROR: Data could not be sent.";			// The error message if the SFML packets cannot send.
		const std::string kDataReceivingErrorMessage = "ERROR: Data could not be received.";	// The error message if the SFML packets cannot be received.
		const std::string kDataReadingErrorMessage = "ERROR: Data could not be read.";			// The error message if the SFML packets cannot be read.
		sf::Clock game_clock_;																	// This will be used to work out the lag offset from the server and to run the game clock for the client.
		
		// Methods.
		// This function will be responsible for displaying any error messages when an error occurs.
		inline void DisplayErrorMessage(const std::string& error_message) { std::cout << error_message << std::endl; }

};


#endif