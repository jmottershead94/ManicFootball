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
		const std::string kDataSendingErrorMessage = "ERROR: Data could not be sent.";			// The error message if the SFML packets cannot send.
		const std::string kDataReceivingErrorMessage = "ERROR: Data could not be received.";	// The error message if the SFML packets cannot be received.
		const std::string kDataReadingErrorMessage = "ERROR: Data could not be read.";			// The error message if the SFML packets cannot be read.
		sf::Clock lag_offset_clock_;															// This will be used to work out the lag offset from the server.

		// Methods.
		Utilities();
		~Utilities();
		void DisplayErrorMessage(const std::string& error_message);

		// The structure for the game's starting message.
		struct StartMessage
		{
			bool player_team;			// What team the player will be on.
			float time;					// The current game time.
		};

		// The structure for the player's input.
		// This will be the main message being sent across from the client to the server.
		struct Input
		{
			bool up;					// If the player is pressing up.
			bool right;					// If the player is pressing right.
			bool left;					// If the player is pressing left.
			float time;					// The current time that the input was given at.
		};
		
		// The structure for correcting dynamic object's positions.
		// This will be sent every so often to make sure that objects are in the correct place.
		struct PositionCorrection
		{
			float x;					// The correct x position.
			float y;					// The correct y position.
			float time;					// The current time that the positions were given at.
		};

};


#endif