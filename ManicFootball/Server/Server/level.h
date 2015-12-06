// Jason Mottershead, 1300455.

// Level class header file.
// This class will contain all of the level objects and information, football, nets, score etc.

// Header guard.
#ifndef _LEVEL_H_
#define _LEVEL_H_

// Include files here.
#include <iostream>
#include "network.h"
#include "level_generator.h"

class Level
{

	public:
		// Methods.
		Level();
		~Level();
		void Init(b2World* world, sf::Font& font, sf::Vector2f& game_screen_resolution, Network& network, sf::Clock& game_clock);
		void UpdateTheScoreboard();
		void UpdateTheScore(int score, int previous_score, std::ostringstream& conversion, bool red_team);
		void CollisionTest();
		void HandleLevelObjects(float dt);
		void DataResponse(sf::TcpSocket& client_socket, sf::Packet& data, DynamicBodyRectangle& object, float dt);
		void ApplyPlayerInput(DynamicBodyRectangle& player, float dt);
		void Update(float dt);

		// Getters.
		// This will return the current level generator.
		inline LevelGenerator& GetLevelGenerator()		{ return level_generator_; }
		
	private:
		// Attributes.
		const b2Vec2 kPlayerMovementForce = {2.0f, 10.0f};		// The force which the players will move at.
		b2World* world_;										// Points to the box2D world.
		sf::Clock* clock_;										// Points to the game clock.
		Network* network_;										// Points to the game network.
		LevelGenerator level_generator_;						// Builds the level and handles rendering.

};

#endif