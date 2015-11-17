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

	// Basically any rage quitters here.
	// If the player presses the escape button.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		// Exit the game.
		window_->close();
	}
	// Otherwise, if the player presses backspace.
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		// Take the player back to the main menu.
		return new MenuState(*this);
	}

	// If the current match has finished.
	if (level_.HasFinished())
	{
		// If the red team won.
		if (level_.GetRedTeamScore() == 3)
		{
			// Go to the winning screen with red team as the winner.
			return new EndMatchState(*this, true);
		}
		// Otherwise, blue team won.
		else
		{
			// Go to the winning screen with blue team as the winner.
			return new EndMatchState(*this, false);
		}
	}

	// USED FOR DEBUGGING.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		level_.Reset();
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
	level_.Init(world_, *font_, *screen_resolution_, network_->GetAssignedTeam(), network_->GetLagOffset());

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
	// Clear the level.
	level_.Clear();

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

	// If the game window exists.
	if (window_)
	{
		// If there are objects in the level.
		if (!level_.GetObjects().empty())
		{
			// Iterating through all of the level objects.
			for (auto level_object = level_.GetObjects().begin(); level_object != level_.GetObjects().end(); level_object++)
			{
				// If the level object has a rectangle shape.
				if ((**level_object).IsRectangle())
				{
					// Therefore, draw the rectangle shape.
					window_->draw((**level_object).GetRectangleShape());
				}
				// Otherwise, the level object will have a circle shape.
				else
				{
					// Draw the circle shape for the football.
					window_->draw((**level_object).GetCircleShape());
				}
			}
		}

		// If there is a set of scores in the level.
		if (!level_.GetScore().empty())
		{
			// Iterating through all of the level scores.
			for (auto score = level_.GetScore().begin(); score != level_.GetScore().end(); score++)
			{
				// Draw the score on the screen.
				window_->draw((**score));
			}
		}
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
// This will provide a timer for this class.			//
//////////////////////////////////////////////////////////
void LevelState::Update(float dt)
{

	// Update the level.
	level_.Update(dt);

}