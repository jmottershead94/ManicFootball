// Jason Mottershead, 1300455.

// Player class header file.
// This class will contain all of the information and functionality to do with the player.

// Header guard.
#ifndef _PLAYER_H_
#define _PLAYER_H_

// Include files here.
#include "dynamic_body_rectangle.h"

// Player IS A Dynamic Body Rectangle, therefore inherits from it.
class Player : public DynamicBodyRectangle
{

	public:
		// Methods.
		Player();
		~Player();
		void Init(sf::Vector2f position, sf::Vector2f dimensions, b2World* world);
		void Input(float dt);
		void Jump(float dt);
		void Respawn();
		void Update(float dt);

	private:
		// Attributes.
		bool in_air_;
		bool respawn_;
		sf::Vector2f respawn_location_;
		sf::Vector2f movement_force_;


};

#endif