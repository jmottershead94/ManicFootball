// Jason Mottershead, 1300455.

// Player class header file.
// This class will contain all of the information and functionality to do with the player.

// Header guard.
#ifndef _PLAYER_TEST__H_
#define _PLAYER_TEST_H_

// Include files here.
#include "physics_engine.h"
#include "game_object.h"

// Player IS A Dynamic Body Rectangle, therefore inherits from it.
class PlayerTest : public GameObject
{

public:
	// Methods.
	PlayerTest();
	~PlayerTest();
	void Init(sf::Vector2f position, sf::Vector2f dimensions, bool red_team, PhysicsEngine& physics);
	void Input(float dt);
	void Jump(float dt);
	void Respawn();
	void Update(float dt);

private:
	// Attributes.
	bool is_red_team_;					// If the player is on the red team or not.
	bool in_air_;						// A flag to determine if the player is in the air or not.
	bool respawn_;						// A flag to determine if the player should respawn or not.
	sf::Vector2f movement_force_;		// A vector2 for the amount of force that should be applied to the player.
	sf::Vector2f respawn_location_;		// A vector2 for the spawn location of the player.
	PhysicsEngine* physics_;


};

#endif