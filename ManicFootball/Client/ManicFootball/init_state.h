// Jason Mottershead, 1300455.

// Init class header file.
// This class will contain all of the necessary information for handling this state.
// In this case, it will display the start screen and start the state machine off.
// As well as load in the graphics-based splash screen and the title screen.

// Header guard.
#ifndef _INIT_STATE_H_
#define _INIT_STATE_H_

// Include files here.
// All of these includes are states that this state will communicate with.
#include "state.h"
#include "menu_state.h"

// Start state IS A state, therefore inherits from it.
class InitState : public State
{

	public:
		// Methods.
		InitState(sf::RenderWindow& window, sf::Font& game_font, sf::Vector2f& game_screen_resolution, b2World* world);
		~InitState();
		State* HandleInput();
		void OnEnter();
		void OnExit();
		void Render();
		void Update(float dt);

};

#endif