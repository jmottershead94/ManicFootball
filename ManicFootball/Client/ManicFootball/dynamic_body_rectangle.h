// Jason Mottershead, 1300455.

// Dynamic Body Rectangle class header file.
// This class will contain all of the information for starting a dynamic body.
// This will be used for setting up the characters in the game (the players).

// Header guard.
#ifndef _DYNAMIC_BODY_RECTANGLE_H_
#define _DYNAMIC_BODY_RECTANGLE_H_

// Include files here.
#include "game_object.h"
#include "messages.h"

// Dynamic Body Rectangle IS A game object, therefore inherits from it.
class DynamicBodyRectangle : public GameObject
{

	public:
		// Methods.
		void Init(sf::Vector2f position, sf::Vector2f dimensions, b2World* world, ObjectID object_id, const sf::Color colour, float bounciness);
		void Update(float dt);

		// Getters.
		// This function will return the input struct that is being used.
		inline Input& GetInput()				{ return input_; }

		// This function will return the current movement force for players.
		inline sf::Vector2f& GetMovementForce()	{ return movement_force_; }

	private:
		// Attributes.
		sf::Vector2f movement_force_;			// A vector2 for the amount of force that should be applied to the player.
		Input input_;							// A struct for our input data.


};

#endif

