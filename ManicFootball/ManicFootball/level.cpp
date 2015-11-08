#include "level.h"


Level::Level() : level_objects_(NULL),
	scores_(NULL)
{
}


Level::~Level()
{
}

void Level::Init(b2World* world, sf::Font& font, sf::Vector2f& game_screen_resolution)
{

	// Initialising local attributes.
	reset_ = false;									// The level does not need resetting right now.
	red_team_score_ = 0;							// The current score of the red team.
	blue_team_score_ = 0;							// The current score of the blue team.
	world_ = world;									// Access to the box2D world.
	font_ = &font;									// Access to the game font.
	screen_resolution_ = &game_screen_resolution;	// Access to the game resolution.
	red_convert_ << red_team_score_;				// Places the textual representation of the red team score integer into red_convert_.
	blue_convert_ << blue_team_score_;				// Places the textual representation of the blue team score integer into blue_convert_.

	CreateGround();
	CreateScoreboard();

}

void Level::CreateGround()
{

	// Allocating memory for the ground when we need it.
	StaticBody* ground = new StaticBody();

	// Initialising the static body for the ground.
	ground->Init(sf::Vector2f(0.0f, 600.0f), sf::Vector2f(1280.0f, 100.0f), world_, ObjectID::surface, sf::Color::Green);
	
	// Adding the game object to the level objects vector.
	level_objects_.push_back(ground);

}

void Level::CreateScoreboard()
{

	// Set up a new text variable.
	sf::Text* red_score_ = new sf::Text();

	// Set the font of the text that is going to be displayed and set what the text will display.
	red_score_->setFont(*font_);
	red_score_->setString(red_convert_.str());
	red_score_->setPosition(screen_resolution_->x * 0.2f, 0.0f);
	red_score_->setCharacterSize(128);
	red_score_->setColor(sf::Color::Red);
	red_score_->setStyle(sf::Text::Bold);

	// Add the red score to the scores vector.
	scores_.push_back(red_score_);

	// Set up a new text variable.
	sf::Text* blue_score = new sf::Text();

	// Set the font of the text that is going to be displayed and set what the text will display.
	blue_score->setFont(*font_);
	blue_score->setString(blue_convert_.str());
	blue_score->setPosition(screen_resolution_->x * 0.75f, 0.0f);
	blue_score->setCharacterSize(128);
	blue_score->setColor(sf::Color::Blue);
	blue_score->setStyle(sf::Text::Bold);

	// Add the blue score to the scores vector.
	scores_.push_back(blue_score);

}

void Level::Reset()
{

}

void Level::CollisionTest()
{

}

void Level::CollisionResponses()
{

}

void Level::Clear()
{

}

void Level::Update(float dt)
{

}