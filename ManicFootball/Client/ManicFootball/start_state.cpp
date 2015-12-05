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

	// Creating a new network connection for the client.
	network_ = new Network();

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

	// Check to see if we have connected to the server.
	if (network_->GetConnection().ToServer())
	{
		// Check to see if we have received any starting messages.
		if (network_->ReceivedStartingMessage())
		{
			// Check to see if the client is now ready.
			if (network_->ReceivedReadyMessage())
			{
				// Initially set to non blocking-mode.
				//network_->GetConnection().GetSocket()->setBlocking(false);

				// Continue with the game.
				return new LevelState(*this);
			}
		}
		//// Otherwise, we have not received a starting message.
		//else
		//{
		//	// Return to the main menu.
		//	return new MenuState(*this);
		//}
	}
	//// Otherwise, we have not connected to the server.
	//else
	//{
	//	// Return to the main menu.
	//	return new MenuState(*this);
	//}

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