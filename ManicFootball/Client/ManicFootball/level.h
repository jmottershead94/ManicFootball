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

class Level
{

	public:
		// Attributes.
		bool finished_;												// Whether the match has finished or not.
		int red_team_score_, blue_team_score_;						// The score values of the two different teams.
		int previous_red_team_score_, previous_blue_team_score_;	// The previous score values used for comparisons.

		// Methods.
		Level();
		~Level();
		void Init(b2World* world, sf::Font& font, sf::Vector2f& game_screen_resolution, Network& game_network);
		void CreateGround();
		void CreateWall(sf::Vector2f& position, sf::Vector2f& dimension);
		void CreateNets(bool left_of_the_field);
		void CreateScoreboard();
		void CreatePlayer(bool red_team);
		void CreateOtherPlayer(bool red_team);
		void CreateFootball(sf::Vector2f& position);
		void Reset();
		void UpdateTheScoreboard();
		void UpdateTheScore(int score, int previous_score, std::ostringstream& conversion, bool red_team);
		void CollisionTest();
		void HandleLevelObjects(float dt);
		void ApplyPlayerInput(DynamicBodyRectangle& player, float dt);
		void CorrectPositions();
		void UpdatePositions();
		void Clear();
		void Update(float dt);

		// Setters.
		// This will increase the red teams score.
		inline void IncrementRedTeamScore() { red_team_score_++; }

		// This will increase the blue teams score.
		inline void IncrementBlueTeamScore() { blue_team_score_++; }

		// Getters.
		// This function will return all of the game objects in the level.
		inline std::vector<GameObject*>& GetObjects() { return level_objects_; }

		// This function will return the vector of scores.
		inline std::vector<sf::Text*>& GetScore() { return scores_; }

		// This function will return if the level has finished or not.
		inline bool HasFinished() { return finished_; }

		// This will return the current red team score.
		inline int GetRedTeamScore() { return red_team_score_; }

		// This will return the current blue team score.
		inline int GetBlueTeamScore() { return blue_team_score_; }

	private:
		// Attributes.
		std::ostringstream red_convert_;			// Convert the red score integer to a string.
		std::ostringstream blue_convert_;			// Convert the blue score integer to a string.
		std::vector<GameObject*> level_objects_;	// The vector of level objects, stores all game objects in the world.
		std::vector<sf::Text*> scores_;				// The vector of level scores.
		sf::Int32 lag_offset_;						// The lag offset for each message from the server.
		b2World* world_;							// Points to the box2D world.
		sf::Font* font_;							// Points to the game font.
		sf::Vector2f* screen_resolution_;			// Points to the screen resolution.
		sf::Clock clock_;							// This will be the game clock for this player.
		Network* network_;							// This will provide us access to the network.

};

#endif