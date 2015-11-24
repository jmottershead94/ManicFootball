// Jason Mottershead, 1300455.

// Level class header file.
// This class will contain all of the level objects and information, players, the football, nets, score etc.

// Header guard.
#ifndef _LEVEL_H_
#define _LEVEL_H_

// Include files here.
#include <array>
#include <iostream>
#include <sstream>
#include <vector>
#include "static_body.h"
#include "dynamic_body_circle.h"
#include "player.h"
#include "network.h"
#include "level_generator.h"

class Level
{

	public:
		// Methods.
		Level();
		~Level();
		void Init(b2World* world, sf::Font& font, sf::Vector2f& game_screen_resolution, Network& game_network);
		void UpdateTheScoreboard();
		void UpdateTheScore(int score, int previous_score, std::ostringstream& conversion, bool red_team);
		void CollisionTest();
		void HandleLevelObjects(float dt);
		void DataResponse(sf::Packet& data, DynamicBodyRectangle& object, float dt);
		void ApplyPlayerInput(DynamicBodyRectangle& player, float dt);
		void CorrectPositions();
		void UpdatePositions();
		void Update(float dt);

		// Getters.
		// This function will return the current level generator.
		inline LevelGenerator& GetLevelGenerator() { return level_generator_; }

	private:
		// Attributes.
		b2World* world_;							// Points to the box2D world.
		sf::Int32 lag_offset_;						// The lag offset for each message from the server.
		sf::Font* font_;							// Points to the game font.
		sf::Vector2f* screen_resolution_;			// Points to the screen resolution.
		sf::Clock clock_;							// This will be the game clock for this player.
		Network* network_;							// This will provide us access to the network.
		LevelGenerator level_generator_;			// Builds the level and handles rendering.

};

#endif