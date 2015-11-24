// Include header file here.
#include "init_state.h"

//////////////////////////////////////////////////////////
//======================================================//
//					Constructor							//
//======================================================//
// This will initialise this state.						//
// Each of the pointers for the entire state machine	//
// will be initialised here, by pointing to the			//
// variables from game class.							//
//////////////////////////////////////////////////////////
// PASS IN CLASSES HERE TO INITIALISE POINTERS IN THE BASE STATE CLASS.
InitState::InitState(sf::RenderWindow& window, sf::Font& game_font, sf::Vector2f& game_screen_resolution, b2World* world)
{

	// Setting up the state pointer variables.
	font_ = &game_font;
	window_ = &window;
	screen_resolution_ = &game_screen_resolution;
	world_ = world;

}

//////////////////////////////////////////////////////////
//======================================================//
//					Destructor							//
//======================================================//
//////////////////////////////////////////////////////////
InitState::~InitState()
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
State* InitState::HandleInput()
{

	// If the player presses the left mouse button.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// Return a new state.
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
void InitState::OnEnter()
{

	// Start init state specific stuff.
	// If the font file has loaded correctly.
	if (font_)
	{
		// Set up a new text variable.
		text_ = new sf::Text();

		// Set the font of the text that is going to be displayed.
		text_->setFont(*font_);
		text_->setPosition(screen_resolution_->x * 0.35f, 0.0f);
		text_->setString("Manic Football");
		text_->setCharacterSize(64);
		text_->setColor(sf::Color::White);
		text_->setStyle(sf::Text::Bold | sf::Text::Underlined);

		// Setting up a new text variable to display controls.
		text_controls_ = new sf::Text();

		text_controls_->setPosition(0.0f, 100.0f);
		text_controls_->setFont(*font_);
		text_controls_->setString("Left mouse button - Main Menu");
		text_controls_->setCharacterSize(32);
		text_controls_->setColor(sf::Color::White);
		text_controls_->setStyle(sf::Text::Bold);
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
void InitState::OnExit()
{

	// Stopping the init state specific stuff.
	

}

//////////////////////////////////////////////////////////
//======================================================//
//						Render							//
//======================================================//
// Render will just draw everything that is in this 	//
// state.												//
//////////////////////////////////////////////////////////
void InitState::Render()
{

	// If the text actually exists, meaning everything has loaded correctly.
	if (text_)
	{
		// Draws the text onto the screen.
		window_->draw(*text_);
	}

	if (text_controls_)
	{
		window_->draw(*text_controls_);
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
// This will provide a timer for this class.			//
//////////////////////////////////////////////////////////
void InitState::Update(float dt)
{
	
}