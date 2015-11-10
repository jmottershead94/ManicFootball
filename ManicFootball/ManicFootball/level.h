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

class Level
{

	public:
		// Attributes.
		bool reset_;								// A flag to determine whether or not the level should be reset.
		int red_team_score_, blue_team_score_;		// The score values of the two different teams.
		
		// Methods.
		Level();
		~Level();
		void Init(b2World* world, sf::Font& font, sf::Vector2f& game_screen_resolution);
		void CreateGround();
		void CreateWall(sf::Vector2f& position, sf::Vector2f& dimension);
		void CreateNets(bool left_of_the_field);
		void CreateScoreboard();
		void CreatePlayer();
		void CreateOtherPlayers();
		void CreateFootball(sf::Vector2f& position);
		void Reset();
		void UpdateScoreboard();
		void RemoveObjects();
		void CheckGoal();
		void CollisionTest();
		void HandleLevelObjects(float dt);
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

	private:
		// Attributes.
		std::vector<GameObject*> level_objects_;	// The vector of level objects, stores all game objects in the world.
		std::vector<sf::Text*> scores_;
		b2World* world_;							// Points to the box2D world.
		sf::Font* font_;							// Points to the game font.
		sf::Vector2f* screen_resolution_;			// Points to the screen resolution.
		std::ostringstream red_convert_;			// Convert the red score integer to a string.
		std::ostringstream blue_convert_;			// Convert the blue score integer to a string.

};

#endif