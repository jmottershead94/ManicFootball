// Include header file here.
#include "menu_state.h"

//////////////////////////////////////////////////////////
//======================================================//
//					Constructor							//
//======================================================//
// This will initialise this state.						//
// Passing in the current state allows for				//
// communication between the states.					//
//////////////////////////////////////////////////////////
MenuState::MenuState(const State& current_state) : State(current_state)
{
}

//////////////////////////////////////////////////////////
//======================================================//
//					Destructor							//
//======================================================//
//////////////////////////////////////////////////////////
MenuState::~MenuState()
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
State* MenuState::HandleInput()
{

	//// If the player pressed the left mouse button.
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	//{
	//	// Return a new state.
	//	//return new "StateClassNameHere"(*this);
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
void MenuState::OnEnter()
{

	// Menu state specific stuff.
	// If the font file has loaded correctly.
	if (font_)
	{
		// Set up a new text variable.
		text_ = new sf::Text();

		// Set the font of the text that is going to be displayed and set what the text will display.
		text_->setFont(*font_);
		text_->setString("The Menu State");
		text_->setCharacterSize(32);
		text_->setColor(sf::Color::Red);
		text_->setStyle(sf::Text::Bold | sf::Text::Underlined);
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
void MenuState::OnExit()
{

	// Stopping the menu state specific stuff.


}

//////////////////////////////////////////////////////////
//======================================================//
//						Render							//
//======================================================//
// Render will just draw everything that is in this 	//
// state.												//
//////////////////////////////////////////////////////////
void MenuState::Render()
{

	// If the text actually exists, meaning everything has loaded correctly.
	if (text_)
	{
		// Draws the text onto the screen.
		window_->draw(*text_);
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
// This will provide a timer for this class.			//
//////////////////////////////////////////////////////////
void MenuState::Update(float dt)
{

}