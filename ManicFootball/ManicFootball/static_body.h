// Jason Mottershead, 1300455.

// Static body class header file.
// This class will contain all of the information for starting a static body.
// This will be used for setting up all of the level objects in the game (apart from players and boxes).

// Header guard.
#ifndef _STATIC_BODY_H_
#define _STATIC_BODY_H_

// Include files here.
#include "game_object.h"

// Static body IS A game object, therefore inherits from it.
class StaticBody : public GameObject
{

	public:
		// Methods.
		StaticBody();
		~StaticBody();
		void Init(sf::Vector2f position, sf::Vector2f dimensions, b2World* world, ObjectID object_id);
		void Update();
		
};

#endif

