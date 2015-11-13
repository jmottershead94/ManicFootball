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
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		return new LevelState(*this);
	}

	// Wait for all of the connections to be made here..
	// All four players to connect here.

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
		text_->setString("Waiting for connections...");
		text_->setPosition(screen_resolution_->x * 0.55f, screen_resolution_->y * 0.25f);
		text_->setCharacterSize(32);
		text_->setColor(sf::Color::Red);
		text_->setStyle(sf::Text::Bold);
	}

	// Just used for testing purposes.
	test_.Init(sf::Vector2f(0.0f, 600.0f), sf::Vector2f(1280.0f, 100.0f), world_, ObjectID::surface, sf::Color::Green, true);
	ball_test_.Init(sf::Vector2f(800.0f, 100.0f), 25.0f, world_, ObjectID::ball, sf::Color::White);
	player_class_.Init(sf::Vector2f(100.0f, 200.0f), sf::Vector2f(25.0f, 75.0f), world_, true);

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

	test_.~StaticBody();
	world_->DestroyBody(test_.GetBody());

	player_class_.~Player();
	world_->DestroyBody(player_class_.GetBody());

	ball_test_.~DynamicBodyCircle();
	world_->DestroyBody(ball_test_.GetBody());

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
		window_->draw(ball_test_.GetCircleShape());
		window_->draw(player_class_.GetRectangleShape());
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

	// Updating the test football.
	ball_test_.Update(dt);

	// Updating the test player.
	player_class_.Update(dt);

}