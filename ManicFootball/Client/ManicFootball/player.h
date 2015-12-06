// Jason Mottershead, 1300455.

// Player class header file.
// This class will contain all of the information and functionality to do with the player.

// Header guard.
#ifndef _PLAYER_H_
#define _PLAYER_H_

// Include files here.
#include <iostream>
#include "dynamic_body_rectangle.h"

// Player IS A Dynamic Body Rectangle, therefore inherits from it.
class Player : public DynamicBodyRectangle
{

	public:
		// Methods.
		void Init(sf::Vector2f position, sf::Vector2f dimensions, b2World* world, bool red_team);
		void Controls(float dt);
		void Update(float dt);

		// Getters.
		// This will return the current input state of the player.
		inline Input& GetInput()	{ return input_; }

	private:
		// Attributes.
		bool is_red_team_;			// Whether or not the player is on the red team.
		Input input_;				// The input struct for the player, whether we are going up, left, or right.

};

#endif