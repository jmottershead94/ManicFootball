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

	// Creating the level.
	CreateGround();
	CreateWalls();
	CreateNets();
	CreateScoreboard();
	CreatePlayer();
	CreateOtherPlayers();
	CreateFootball();

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

void Level::CreateWalls()
{

	// Allocating memory for the ground when we need it.
	StaticBody* ground = new StaticBody();

	// Initialising the static body for the ground.
	ground->Init(sf::Vector2f(0.0f, 600.0f), sf::Vector2f(1280.0f, 100.0f), world_, ObjectID::surface, sf::Color::Green);
	
	// Adding the game object to the level objects vector.
	level_objects_.push_back(ground);

}

void Level::CreateNets()
{

}

void Level::CreateScoreboard()
{

	// Allocating memory for the text when we need it.
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

	// Allocating memory for the text when we need it.
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

void Level::CreatePlayer()
{

	// Allocating memory for the player when we need it.
	Player* player = new Player();

	// Initialising the player on the red team.
	player->Init(sf::Vector2f(200.0f, 200.0f), sf::Vector2f(25.0f, 75.0f), world_, true);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(player);

}

void Level::CreateOtherPlayers()
{

	// Allocating memory for the other player when we need it.
	DynamicBodyRectangle* other_player = new DynamicBodyRectangle();

	// Initialising the dynamic body for the other player on the red team.
	other_player->Init(sf::Vector2f(400.0f, 200.0f), sf::Vector2f(25.0f, 75.0f), world_, ObjectID::otherPlayer, sf::Color::Red);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(other_player);

}

void Level::CreateFootball()
{

	// Allocating memory for the football when we need it.
	DynamicBodyCircle* football = new DynamicBodyCircle();

	// Initialising the dynamic body for the football.
	football->Init(sf::Vector2f(screen_resolution_->x * 0.5f, screen_resolution_->y * 0.25f), 25.0f, world_, ObjectID::ball, sf::Color::White);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(football);

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

void Level::HandleLevelObjects(float dt)
{
	
	// If there are objects in the level.
	if (!level_objects_.empty())
	{
		// Iterating through all of the level objects.
		for (auto level_object = level_objects_.begin(); level_object != level_objects_.end(); level_object++)
		{
			// If the level object is a football.
			if ((**level_object).GetID() == ObjectID::ball)
			{
				// Casting this to a dynamic body circle in order to update the sprites position for level object.
				DynamicBodyCircle* temp = static_cast<DynamicBodyCircle*>(*level_object);
				temp->Update(dt);
			}
			// Otherwise, if the object is a player.
			else if ((**level_object).GetID() == ObjectID::player)
			{
				// Casting this to a player in order to update the sprites position for level object.
				Player* temp = static_cast<Player*>(*level_object);
				temp->Update(dt);
			}
			// Otherwise, the object is another player.
			else if ((**level_object).GetID() == ObjectID::otherPlayer)
			{
				// Casting this to a dynamic body rectangle in order to update the sprites position for level object.
				DynamicBodyRectangle* temp = static_cast<DynamicBodyRectangle*>(*level_object);
				temp->Update(dt);
			}
		}
	}

}

void Level::Clear()
{

}

void Level::Update(float dt)
{

	HandleLevelObjects(dt);

}