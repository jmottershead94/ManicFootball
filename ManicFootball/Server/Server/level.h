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
		// Attributes.
		//int red_team_score_, blue_team_score_;						// The score values of the two different teams.
		//int previous_red_team_score_, previous_blue_team_score_;	// The previous score values used for comparisons.

		// Methods.
		Level();
		~Level();
		void Init(b2World* world, sf::Font& font, sf::Vector2f& game_screen_resolution, Network& network, sf::Clock& game_clock);
		/*void CreateGround();
		void CreateWall(sf::Vector2f& position, sf::Vector2f& dimension);
		void CreateNets(bool left_of_the_field);
		void CreateScoreboard();
		void CreatePlayer(bool red_team);
		void CreateFootball(sf::Vector2f& position);
		void Reset();*/
		void UpdateTheScoreboard();
		void UpdateTheScore(int score, int previous_score, std::ostringstream& conversion, bool red_team);
		void CollisionTest();
		void HandleLevelObjects(float dt);
		void CheckPlayerInput(DynamicBodyRectangle& player, float dt);
		void MovePlayers(float dt);
		void ApplyPlayerInput(DynamicBodyRectangle& player, float dt);
		void CorrectPositions(sf::TcpSocket& client_socket, std::vector<double>& player_x, std::vector<double>& player_y, tk::spline& player_interpolation);
		void StorePositions();
		//void Clear();
		//void Render(sf::RenderWindow& game_window);
		void Update(float dt);

		// Setters.
		// This will increase the red teams score.
		//inline void IncrementRedTeamScore()			{ red_team_score_++; }

		// This will increase the blue teams score.
		//inline void IncrementBlueTeamScore()			{ blue_team_score_++; }

		// Getters.
		// This will return the current level generator.
		inline LevelGenerator& GetLevelGenerator()		{ return level_generator_; }

		// This function will return all of the game objects in the level.
		//inline std::vector<GameObject*>& GetObjects()	{ return level_objects_; }
		
		//// This function will return if the level has finished or not.
		//inline bool HasFinished()						{ return finished_; }

		// This will return the current red team score.
		//inline int GetRedTeamScore()					{ return red_team_score_; }

		// This will return the current blue team score.
		//inline int GetBlueTeamScore()					{ return blue_team_score_; }

	private:
		// Attributes.
		const b2Vec2 kPlayerMovementForce = {2.0f, 10.0f};		// The force which the players will move at.
		b2World* world_;										// Points to the box2D world.
		std::vector < double > player_one_x_, player_one_y_;
		std::vector < double > player_two_x_, player_two_y_;
		//std::vector<GameObject*> level_objects_;				// The vector of level objects, stores all game objects in the world.
		//std::vector<sf::Text*> scores_;							// The vector for keeping track of scores.
		tk::spline player_one_spline_;							// Used for position prediction.
		tk::spline player_two_spline_;
		sf::Font* font_;										// Points to the game font.
		sf::Vector2f* screen_resolution_;						// Points to the screen resolution.
		sf::Clock clock_;										// Points to the game clock.
		//std::ostringstream red_convert_;						// Convert the red score integer to a string.
		//std::ostringstream blue_convert_;						// Convert the blue score integer to a string.
		Network* network_;										// Points to the game network.
		LevelGenerator level_generator_;						// Builds the level and handles rendering.

};

#endif