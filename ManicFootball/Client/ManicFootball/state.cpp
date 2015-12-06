// Include header file here.
#include "state.h"

//////////////////////////////////////////////////////////
//======================================================//
//						Cleanup							//
//======================================================//
// This function will clean up all of the pointer		//
// variables that are shared across all of the other	//
// states.												//
//////////////////////////////////////////////////////////
void State::Cleanup()
{

	// Clean up all of the pointer variables.
	if (window_)
	{
		delete window_;
		window_ = nullptr;
	}

	if (text_)
	{
		delete text_;
		text_ = nullptr;
	}

	if (text_controls_)
	{
		delete text_controls_;
		text_controls_ = nullptr;
	}

	if (network_)
	{
		delete network_;
		network_ = nullptr;
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
// This will update the states every frame.				//
//////////////////////////////////////////////////////////
void State::Update(float dt)
{
}