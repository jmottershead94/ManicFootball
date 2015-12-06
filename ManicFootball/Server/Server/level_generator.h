// Jason Mottershead, 1300455.

// Level Generator class header file.
// This class will be responsible for generating all of the game objects in the level.

// Header guard.
#ifndef _LEVEL_GENERATOR_H_
#define _LEVEL_GENERATOR_H_

#include <array>
#include <sstream>
#include "static_body.h"
#include "dynamic_body_rectangle.h"

class LevelGenerator
{

	public:
		// Attributes.
		std::ostringstream red_convert_;							// Convert the red score integer to a string.
		std::ostringstream blue_convert_;							// Convert the blue score integer to a string.

		// Methods.
		LevelGenerator();
		~LevelGenerator();
		void Init(b2World* world, sf::Font& font, sf::Vector2f& game_screen_resolution);
		void BuildLevel();
		void CreateGround();
		void CreateWall(sf::Vector2f& position, sf::Vector2f& dimension);
		void CreateNets(bool left_of_the_field);
		void CreateScoreboard();
		void CreatePlayer(bool red_team);
		void CreateFootball(sf::Vector2f& position);
		void Reset();
		void Clear();
		void Render(sf::RenderWindow& game_window);

		// Setters.
		// This will set the current finish state of the match.
		inline void SetFinished(bool has_finished)					{ finished_ = has_finished; }

		// This will increment the red team score by 1.
		inline void IncrementRedTeamScore()							{ red_team_score_++; }

		// This will increment the blue team score by 1.
		inline void IncrementBlueTeamScore()						{ blue_team_score_++; }

		// This will set the previous red team score to a new value.
		inline void SetPreviousRedTeamScore(int previous_score)		{ previous_red_team_score_ = previous_score; }

		// This will set the previous blue team score to a new value.
		inline void SetPreviousBlueTeamScore(int previous_score)	{ previous_blue_team_score_ = previous_score; }

		// Getters.
		// This function will return if the level has finished or not.
		inline bool HasFinished()							{ return finished_; }

		// This will return the current red team score.
		inline int GetRedTeamScore()						{ return red_team_score_; }

		// This will return the current blue team score.
		inline int GetBlueTeamScore()						{ return blue_team_score_; }

		// This will return the previous red team score.
		inline int GetPreviousRedTeamScore()				{ return previous_red_team_score_; }

		// This will return the previous blue team score.
		inline int GetPreviousBlueTeamScore()				{ return previous_blue_team_score_; }
		
		// This will return the array of scores.
		inline std::array<sf::Text*, 2> GetScoresText()		{ return scores_; }

		// This will return the vector of game objects in the level.
		inline std::vector<GameObject*> GetLevelObjects()	{ return level_objects_; }

	private:
		// Attributes.
		bool finished_;												// Whether the match has finished or not.
		int red_team_score_, blue_team_score_;						// The score values of the two different teams.
		int previous_red_team_score_, previous_blue_team_score_;	// The previous score values used for comparisons.
		std::array<sf::Text*, 2> scores_;							// The array for storing scores.
		std::vector<GameObject*> level_objects_;					// The vector of level objects, stores all game objects in the world.
		b2World* world_;											// Points to the Box2D world.
		sf::Font* font_;											// Points to the game font.
		sf::Vector2f* screen_resolution_;							// Points to the screen resolution.
};

#endif