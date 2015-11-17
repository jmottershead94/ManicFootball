// Include header file here.
#include "start_state.h"

//////////////////////////////////////////////////////////
//======================================================//
//					Constructor							//
//======================================================//
// This will initialise this state.						//
// Passing in the current state allows for				//
// communication between the states.					//
//////////////////////////////////////////////////////////
StartState::StartState(const State& current_state) : State(current_state)
{
}

//////////////////////////////////////////////////////////
//======================================================//
//					Destructor							//
//======================================================//
//////////////////////////////////////////////////////////
StartState::~StartState()
{
}

//////////////////////////////////////////////////////////
//======================================================//
//					HandleInput							//
//======================================================//
// This function will handle all of the user input.		//
// This function also allows the states to change to	//
// each other, by return a pointer of state.			//
// If there is a state transition, it will be placed	//
// here.												//
//////////////////////////////////////////////////////////
State* StartState::HandleInput()
{

	// If the player presses the escape button.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		// Close the window.
		window_->close();
	}
	/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		return new LevelState(*this);
	}*/

	// Creating a new socket.
	socket_ = new sf::TcpSocket();

	// Wait for all of the connections to be made here..
	// Try and connect to the server.
	// Use the created socket and connect to 127.0.0.1 (this machine) on port 5000, and use the default time out for this machine.
	sf::Socket::Status status = socket_->connect(server_ip_address_, port_);

	// If the socket has connected to the server.
	if (status == sf::Socket::Done)
	{
		// Start the lag timer.
		lag_offset_clock_.restart();
		
		std::cout << "Connected to the server: " << server_ip_address_ << std::endl;

		// Receive some data from the server for deciding what team the player is on.
		// Pass the bool into the below function.
		// And save the timestamp from the server.
		// Work out a latency time offset.
		StartMessage starting_message;

		// Clear the packet.
		data_.clear();

		// If our socket has received some data.
		if (socket_->receive(data_) == sf::Socket::Done)
		{
			// Check to see if it is okay to read the data.
			if (data_ >> starting_message)
			{
				// We have read some data from the starting message!
				float RRT;
				sf::Time lag;

				// Get the current time, and the round trip time from the server message.
				lag = lag_offset_clock_.getElapsedTime();
				RRT = starting_message.time;

				
				std::cout << "The lag client side is = " << lag.asSeconds() << std::endl;
				std::cout << "The lag server side is = " << RRT << std::endl;

				// Calculate the lag offset.
				lag_offset_ = lag.asSeconds() - (RRT / 2.0f);

				// TESTING.
				std::cout << "The lag offset is = " << lag_offset_ << std::endl;

				// Store what team the player will be on.
				bool team = starting_message.player_team;

				// Clear the packet.
				data_.clear();

				// Wait for the second player to connect.
				if (socket_->receive(data_) == sf::Socket::Done)
				{
					// Check to see if it is okay to read the data.
					if (data_ >> ready_)
					{
						// Go to the level, with the team set from the server.
						return new LevelState(*this, team);
					}
					else
					{
						// The packet is not okay to read.
						std::cout << "ERROR: Unable to read the data." << std::endl;
					}
				}
			}
			else
			{
				// The packet is not okay to read.
				std::cout << "ERROR: Unable to read the data." << std::endl;
			}
			// We were unable to read some data from the starting message.
			std::cout << "ERROR: Could not read the message from the server." << std::endl;
		}
		else
		{
			// We were unable to read some data from the starting message.
			std::cout << "ERROR: Could not read the message from the server." << std::endl;
		}
	}
	else
	{
		std::cout << "ERROR: Could not connect to the server." << std::endl;

		// Error, the socket did not connect to the requested server.
		// Go back to the main menu.
		return new MenuState(*this);
	}

	// Returns nothing because there has been no input from the player yet.
	return nullptr;

}

//////////////////////////////////////////////////////////
//======================================================//
//						OnEnter							//
//======================================================//
// This function will be called every time a new state	//
// is created.											//
// This will contain some state specific functions.		//
//////////////////////////////////////////////////////////
void StartState::OnEnter()
{

	// Start state specific stuff.
	// If the font file has loaded correctly.
	if (font_)
	{
		// Set up a new text variable.
		text_ = new sf::Text();

		// Set the font of the text that is going to be displayed and set what the text will display.
		text_->setFont(*font_);
		text_->setString("Waiting for players...");
		text_->setPosition(screen_resolution_->x * 0.2f, screen_resolution_->y * 0.25f);
		text_->setCharacterSize(64);
		text_->setColor(sf::Color::White);
		text_->setStyle(sf::Text::Bold);
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//						OnExit							//
//======================================================//
// This function will be called every time a new state	//
// is destroyed.										//
// This will contain some state specific functions.		//
//////////////////////////////////////////////////////////
void StartState::OnExit()
{

	// Stopping the start state specific stuff.
	if (text_)
	{
		// Remove the "connection" text from the screen.
		text_->~Text();
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//						Render							//
//======================================================//
// Render will just draw everything that is in this 	//
// state.												//
//////////////////////////////////////////////////////////
void StartState::Render()
{

	// If the game window exists.
	if (window_)
	{
		// If the text actually exists, meaning everything has loaded correctly.
		if (text_)
		{
			// Draws the text onto the screen.
			window_->draw(*text_);
		}
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
// This will provide a timer for this class.			//
//////////////////////////////////////////////////////////
void StartState::Update(float dt)
{
}