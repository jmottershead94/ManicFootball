// Jason Mottershead, 1300455.

// Menu class header file.
// This class will contain all of the necessary information for handling this state.
// In this case, it will display the main menu.
// From here the player can access any of the other features in the game.

// Header guard.
#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

// Include files here.
// All of these includes are states that this state will communicate with.
#include "state.h"
#include "start_state.h"
//#include "options_state.h"
//#include "credits_state.h"
//#include "exit_state.h"

// Menu state IS A state, therefore inherits from it.
class MenuState : public State
{

	public:
		// Methods.
		MenuState(const State& current_state);
		~MenuState();
		State* HandleInput();
		void OnEnter();
		void OnExit();
		void Render();
		void Update(float dt);

	private:
		// Attributes.
		sf::Text* menu_controls_;

};

#endif