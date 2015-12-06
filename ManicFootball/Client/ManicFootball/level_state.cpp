// Include header file here.
#include "level_state.h"

//////////////////////////////////////////////////////////
//======================================================//
//					Constructor							//
//======================================================//
// This will initialise this state.						//
// Passing in the current state allows for				//
// communication between the states.					//
//////////////////////////////////////////////////////////
LevelState::LevelState(const State& current_state) : State(current_state)
{
}

//////////////////////////////////////////////////////////
//======================================================//
//					Destructor							//
//======================================================//
//////////////////////////////////////////////////////////
LevelState::~LevelState()
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
State* LevelState::HandleInput()
{

	// If the current match has finished.
	if (level_.GetLevelGenerator().HasFinished())
	{
		// Go to the end match screen.
		return new EndMatchState(*this);		
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
void LevelState::OnEnter()
{
	
	// Starting the level state specific stuff.
	// Load the level.
	level_.Init(world_, *font_, *screen_resolution_, *network_);

}

//////////////////////////////////////////////////////////
//======================================================//
//						OnExit							//
//======================================================//
// This function will be called every time a new state	//
// is destroyed.										//
// This will contain some state specific functions.		//
//////////////////////////////////////////////////////////
void LevelState::OnExit()
{

	// Stopping the level state specific stuff.
	level_.GetLevelGenerator().Reset();

	// Clear the level.
	level_.GetLevelGenerator().Clear();

}

//////////////////////////////////////////////////////////
//======================================================//
//						Render							//
//======================================================//
// Render will just draw everything that is in this 	//
// state.												//
//////////////////////////////////////////////////////////
void LevelState::Render()
{

	// If there are objects in the level.
	if (!level_.GetLevelGenerator().GetLevelObjects().empty())
	{
		// Iterating through all of the level objects.
		for (auto& level_object : level_.GetLevelGenerator().GetLevelObjects())
		{
			// Therefore, draw the rectangle shape.
			window_->draw(level_object->GetRectangleShape());
		}
	}

	// If there is a set of scores in the level.
	if (!level_.GetLevelGenerator().GetScoresText().empty())
	{
		// Iterating through all of the level scores.
		for (auto& score : level_.GetLevelGenerator().GetScoresText())
		{
			// Draw the score on the screen.
			window_->draw(*score);
		}
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
// This will update the states every frame.				//
//////////////////////////////////////////////////////////
void LevelState::Update(float dt)
{

	// Update the level.
	level_.Update(dt);

}