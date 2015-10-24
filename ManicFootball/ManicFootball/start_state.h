// Jason Mottershead, 1300455.

// Start class header file.
// This class will contain all of the necessary information for handling this state.
// In this case, the player will start the game by looking for a server.

// Header guard.
#ifndef _START_STATE_H_
#define _START_STATE_H_

// Include files here.
// All of these includes are states that this state will communicate with.
#include "state.h"
#include "menu_state.h"

// Menu state IS A state, therefore inherits from it.
class StartState : public State
{

	public:
		// Methods.
		StartState(const State& current_state);
		~StartState();
		State* HandleInput();
		void OnEnter();
		void OnExit();
		void Render();
		void Update(float dt);

	private:
		// Attributes.


};

#endif