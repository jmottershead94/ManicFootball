// Jason Mottershead, 1300455.

// End Match State class header file.
// This class will contain all of the necessary information for handling this state.
// In this case, it will start the game and make the player wait for a server connection.

// Header guard.
#ifndef _END_MATCH_STATE_H_
#define _END_MATCH_STATE_H_

// Include files here.
// All of these includes are states that this state will communicate with.
#include "state.h"
#include "menu_state.h"
#include "level.h"
#include "level_test.h"

// Menu state IS A state, therefore inherits from it.
class EndMatchState : public State
{

	public:
		// Methods.
		EndMatchState(const State& current_state, bool red_winning_team);
		~EndMatchState();
		State* HandleInput();
		void OnEnter();
		void OnExit();
		void Render();
		void Update(float dt);

	private:
		// Attributes.
		bool red_won_;

};

#endif