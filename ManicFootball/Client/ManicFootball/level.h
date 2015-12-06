// Jason Mottershead, 1300455.

// Level class header file.
// This class will contain all of the level objects and information, football, nets, score etc.

// Header guard.
#ifndef _LEVEL_H_
#define _LEVEL_H_

// Include files here.
#include <iostream>
#include "level_generator.h"
#include "interpolation.h"

class Level
{

	public:
		// Methods.
		Level();
		~Level();
		void Init(b2World* world, sf::Font& font, sf::Vector2f& game_screen_resolution, Network& game_network);
		void UpdateTheScoreboard();
		void UpdateTheScore(int score, int previous_score, std::ostringstream& conversion, bool red_team);
		void HandleLevelObjects(float dt);
		void DataResponse(sf::Packet& data, DynamicBodyRectangle& object, float dt);
		void ApplyPlayerInput(DynamicBodyRectangle& player, float dt);
		void CorrectPositions(float dt);
		void Update(float dt);

		// Getters.
		// This function will return the current level generator.
		inline LevelGenerator& GetLevelGenerator() { return level_generator_; }

	private:
		// Attributes.
		Network* network_;											// This will provide us access to the network.
		LevelGenerator level_generator_;							// Builds the level and handles rendering.
		Interpolation other_player_;
		Interpolation ball_;
};

#endif