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
		DynamicBodyRectangle();
		~DynamicBodyRectangle();
		void Init(sf::Vector2f position, sf::Vector2f dimensions, b2World* world, ObjectID object_id, const sf::Color colour, float bounciness);
		void Update(float dt);

		// Getters.
		// This function will return the input struct that is being used.
		inline Input& GetInput() { return input_; }

	private:
		// Attributes.
		Input input_;

};

#endif

