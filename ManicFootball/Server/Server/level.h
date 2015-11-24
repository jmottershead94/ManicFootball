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
#include "tk_spline.h"
#include "static_body.h"
#include "dynamic_body_circle.h"
#include "dynamic_body_rectangle.h"
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
		void CheckPlayerInput(DynamicBodyRectangle& player, float dt);
		void MovePlayers(float dt);
		void ApplyPlayerInput(DynamicBodyRectangle& player, float dt);
		void CorrectPositions(sf::TcpSocket& client_socket, std::vector<double>& player_x, std::vector<double>& player_y, tk::spline& player_interpolation);
		void StorePositions();
		void Update(float dt);

		// Getters.
		// This will return the current level generator.
		inline LevelGenerator& GetLevelGenerator()		{ return level_generator_; }

	private:
		// Attributes.
		const b2Vec2 kPlayerMovementForce = {2.0f, 10.0f};		// The force which the players will move at.
		b2World* world_;										// Points to the box2D world.
		std::vector < double > player_one_x_, player_one_y_;	// Will be used for DR.
		std::vector < double > player_two_x_, player_two_y_;	// Will be used for DR.
		tk::spline player_one_spline_;							// Used for DR.
		tk::spline player_two_spline_;							// Used for DR.
		sf::Font* font_;										// Points to the game font.
		sf::Vector2f* screen_resolution_;						// Points to the screen resolution.
		sf::Clock* clock_;										// Points to the game clock.
		Network* network_;										// Points to the game network.
		LevelGenerator level_generator_;						// Builds the level and handles rendering.

};

#endif