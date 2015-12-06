// Jason Mottershead, 1300455.

// Start State class header file.
// This class will contain all of the necessary information for handling this state.
// In this case, it will start the game and make the player wait for a server connection.

// Header guard.
#ifndef _START_STATE_H_
#define _START_STATE_H_

// Include files here.
// All of these includes are states that this state will communicate with.
#include "state.h"
#include "level_state.h"

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

};

#endif