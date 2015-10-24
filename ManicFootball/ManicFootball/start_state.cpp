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
void StartState::OnEnter()
{

	// Menu state specific stuff.
	// If the font file has loaded correctly.
	if (font_)
	{
		// Set up a new text variable.
		text_ = new sf::Text();

		// Set the font of the text that is going to be displayed and set what the text will display.
		text_->setFont(*font_);
		text_->setString("The Start State");
		text_->setCharacterSize(32);
		text_->setColor(sf::Color::Red);
		text_->setStyle(sf::Text::Bold | sf::Text::Underlined);
	}

	test_.Init(sf::Vector2f(0.0f, 600.0f), sf::Vector2f(1280.0f, 100.0f), world_, ObjectID::surface);
	player_test_.Init(sf::Vector2f(500.0f, 200.0f), sf::Vector2f(25.0f, 75.0f), world_, ObjectID::player);
	ball_test_.Init(sf::Vector2f(800.0f, 100.0f), 25.0f, world_, ObjectID::ball);
	// Setting a football up.
	/*football_.setRadius(50);
	football_.setPosition(400.0f, 400.0f);
	football_.setFillColor(sf::Color::White);*/

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

	// Stopping the menu state specific stuff.


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

		window_->draw(test_.GetRectangleShape());
		window_->draw(player_test_.GetRectangleShape());
		window_->draw(ball_test_.GetCircleShape());
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

	// Updating the test player.
	player_test_.Update(dt);

	// Updating the test football.
	ball_test_.Update(dt);

}