// Jason Mottershead, 1300455.

// Level State class header file.
// This class will contain all of the necessary information for handling this state.
// In this case, it will start the game and make the player wait for a server connection.

// Header guard.
#ifndef _LEVEL_STATE_H_
#define _LEVEL_STATE_H_

// Include files here.
// All of these includes are states that this state will communicate with.
#include "state.h"
#include "menu_state.h"
#include "level.h"

// Menu state IS A state, therefore inherits from it.
class LevelState : public State
{

	public:
		// Methods.
		LevelState(const State& current_state);
		~LevelState();
		State* HandleInput();
		void OnEnter();
		void OnExit();
		void Render();
		void Update(float dt);

	private:
		// Attributes.
		Level level_;

};

#endif