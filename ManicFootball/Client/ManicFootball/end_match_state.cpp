// Include header file here.
#include "end_match_state.h"

//////////////////////////////////////////////////////////
//======================================================//
//					Constructor							//
//======================================================//
// This will initialise this state.						//
// Passing in the current state allows for				//
// communication between the states.					//
//////////////////////////////////////////////////////////
EndMatchState::EndMatchState(const State& current_state, bool red_winning_team) : State(current_state),
	red_won_(red_winning_team)
{
}

//////////////////////////////////////////////////////////
//======================================================//
//					Destructor							//
//======================================================//
//////////////////////////////////////////////////////////
EndMatchState::~EndMatchState()
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
State* EndMatchState::HandleInput()
{

	// Basically any rage quitters here.
	// If the player presses the escape button.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		// Exit the game.
		window_->close();
	}
	// If the number 1 has been pressed.
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
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
void EndMatchState::OnEnter()
{

	// Starting the state specific stuff.
	// If the red team won.
	if (red_won_)
	{
		// Display red winner text.
		text_ = new sf::Text();
		text_->setFont(*font_);
		text_->setPosition((screen_resolution_->x * 0.25f), (screen_resolution_->y * 0.3f));
		text_->setString("The Red Team Won!");
		text_->setCharacterSize(64);
		text_->setColor(sf::Color::Red);
		text_->setStyle(sf::Text::Bold);
	}
	// Otherwise, if the blue team won.
	else
	{
		// Display blue winner text.
		text_ = new sf::Text();
		text_->setFont(*font_);
		text_->setPosition((screen_resolution_->x * 0.25f), (screen_resolution_->y * 0.3f));
		text_->setString("The Blue Team Won!");
		text_->setCharacterSize(64);
		text_->setColor(sf::Color::Blue);
		text_->setStyle(sf::Text::Bold);
	}

	// Display controls.
	text_controls_ = new sf::Text();
	text_controls_->setFont(*font_);
	text_controls_->setPosition((screen_resolution_->x * 0.3f), (screen_resolution_->y * 0.75f));
	text_controls_->setString("Press M - Main Menu");
	text_controls_->setCharacterSize(32);
	text_controls_->setColor(sf::Color::White);
	text_controls_->setStyle(sf::Text::Bold);

}

//////////////////////////////////////////////////////////
//======================================================//
//						OnExit							//
//======================================================//
// This function will be called every time a new state	//
// is destroyed.										//
// This will contain some state specific functions.		//
//////////////////////////////////////////////////////////
void EndMatchState::OnExit()
{

	// Stopping the state specific stuff.
	text_->~Text();
	text_controls_->~Text();

}

//////////////////////////////////////////////////////////
//======================================================//
//						Render							//
//======================================================//
// Render will just draw everything that is in this 	//
// state.												//
//////////////////////////////////////////////////////////
void EndMatchState::Render()
{

	// If the game window exists.
	if (window_)
	{
		// Draw the winner text.
		window_->draw(*text_);
		window_->draw(*text_controls_);
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
// This will provide a timer for this class.			//
//////////////////////////////////////////////////////////
void EndMatchState::Update(float dt)
{



}