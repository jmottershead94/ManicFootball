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
InitState::InitState(sf::RenderWindow& window, sf::Font& game_font, sf::Vector2f& game_screen_resolution, b2World* world)
{

	// Setting up the state pointer variables.
	font_ = &game_font;								// Pointing to the game font.
	window_ = &window;								// Pointing to the game render window.
	screen_resolution_ = &game_screen_resolution;	// Pointing to the game screen resolution.
	world_ = world;									// Pointing to the game world.

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

	// Returns the menu state because there has is no input from the player yet.
	return new MenuState(*this);

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
}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
// This will update the states every frame.				//
//////////////////////////////////////////////////////////
void InitState::Update(float dt)
{	
}