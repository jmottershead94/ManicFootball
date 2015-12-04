#include "level_generator.h"

LevelGenerator::LevelGenerator()
{
}

LevelGenerator::~LevelGenerator()
{
}

void LevelGenerator::Init(b2World* world, sf::Font& font, sf::Vector2f& game_screen_resolution)
{

	// Initialising the level generator attributes.
	finished_ = false;								// The match has not yet finished.
	red_team_score_ = 2;							// The current score of the red team.
	blue_team_score_ = 2;							// The current score of the blue team.
	previous_red_team_score_ = red_team_score_;		// The current previous score of the red team.
	previous_blue_team_score_ = blue_team_score_;	// The current previous score of the blue team.
	red_convert_ << red_team_score_;				// Places the textual representation of the red team score integer into red_convert_.
	blue_convert_ << blue_team_score_;				// Places the textual representation of the blue team score integer into blue_convert_.
	world_ = world;									// Access to the box2D world.
	font_ = &font;									// Access to the game font.
	screen_resolution_ = &game_screen_resolution;	// Access to the game resolution.

	BuildLevel();
}

void LevelGenerator::BuildLevel()
{

	// Creating the level.
	CreateGround();
	CreateWall(sf::Vector2f(0.0f, 0.0f), sf::Vector2f((screen_resolution_->x * 0.0675f), screen_resolution_->y));
	CreateWall(sf::Vector2f(0.0f, (screen_resolution_->y - (screen_resolution_->y * 0.0675f))), sf::Vector2f(screen_resolution_->x, (screen_resolution_->y * 0.0675f)));
	CreateWall(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(screen_resolution_->x, screen_resolution_->y * 0.0675f));
	CreateWall(sf::Vector2f((screen_resolution_->x - (screen_resolution_->x * 0.0675f)), 0.0f), sf::Vector2f((screen_resolution_->x * 0.0675f), screen_resolution_->y));
	CreateNets(true);
	CreateNets(false);
	CreateScoreboard();
	CreatePlayer(true);
	CreatePlayer(false);
	//CreateFootball(sf::Vector2f(screen_resolution_->x * 0.25f, screen_resolution_->y * 0.25f));
	CreateFootball(sf::Vector2f(screen_resolution_->x * 0.5f, screen_resolution_->y * 0.25f));
	//CreateFootball(sf::Vector2f(screen_resolution_->x * 0.75f, screen_resolution_->y * 0.25f));

}

void LevelGenerator::CreateGround()
{

	// Allocating memory for the ground when we need it.
	StaticBody* ground = new StaticBody();

	// Initialising the static body for the ground.
	ground->Init(sf::Vector2f(0.0f, (screen_resolution_->y - (screen_resolution_->y * 0.0675f)) - (screen_resolution_->y * 0.0625f)), sf::Vector2f(screen_resolution_->x, (screen_resolution_->y * 0.0625f)), world_, ObjectID::surface, sf::Color::Green, true);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(ground);

}

void LevelGenerator::CreateWall(sf::Vector2f& position, sf::Vector2f& dimension)
{

	// Allocating memory for the ground when we need it.
	StaticBody* wall = new StaticBody();

	// Initialising the static body for the ground.
	wall->Init(sf::Vector2f(position.x, position.y), sf::Vector2f(dimension.x, dimension.y), world_, ObjectID::surface, sf::Color::Black, true);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(wall);

}

void LevelGenerator::CreateNets(bool left_of_the_field)
{

	// Allocating memory for the crossbar when we need it.
	StaticBody* crossbar = new StaticBody();

	// Allocating memory for the net when we need it.
	StaticBody* net = new StaticBody();

	// If the nets should be to the left of the field.
	if (left_of_the_field)
	{
		// Initialising the static body for the crossbar.
		crossbar->Init(sf::Vector2f((screen_resolution_->x * 0.0675f), (screen_resolution_->y * 0.64f)), sf::Vector2f(screen_resolution_->x * 0.125f, screen_resolution_->y * 0.0625f), world_, ObjectID::surface, sf::Color::Red, false);

		// Initialising the static body for the back of the net.
		net->Init(sf::Vector2f(crossbar->GetPosition().x, (crossbar->GetPosition().y + crossbar->GetDimension().y + (screen_resolution_->y * 0.000675f))), sf::Vector2f(screen_resolution_->x * 0.03125f, screen_resolution_->y * 0.17f), world_, ObjectID::redNet, sf::Color::Red, false);
	}
	// Otherwise, the nets should be on the right side of the field.
	else
	{
		// Initialising the static body for the crossbar.
		crossbar->Init(sf::Vector2f((screen_resolution_->x - (screen_resolution_->x * 0.0675f) - (screen_resolution_->x * 0.125f)), (screen_resolution_->y * 0.64f)), sf::Vector2f((screen_resolution_->x * 0.125f), (screen_resolution_->y * 0.0625f)), world_, ObjectID::surface, sf::Color::Blue, false);

		// Initialising the static body for the back of the net.
		net->Init(sf::Vector2f((crossbar->GetPosition().x + crossbar->GetDimension().x - (screen_resolution_->x * 0.03125f)), (crossbar->GetPosition().y + crossbar->GetDimension().y + (screen_resolution_->y * 0.000675f))), sf::Vector2f((screen_resolution_->x * 0.03125f), screen_resolution_->y * 0.17f), world_, ObjectID::blueNet, sf::Color::Blue, false);
	}

	// Adding the game object to the level objects vector.
	level_objects_.push_back(crossbar);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(net);

}

void LevelGenerator::CreateScoreboard()
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
	scores_[0] = red_score_;

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
	scores_[1] = blue_score;

}

void LevelGenerator::CreatePlayer(bool red_team)
{

	// Allocating memory for the player when we need it.
	DynamicBodyRectangle* player = new DynamicBodyRectangle();

	// If the player is on the red team.
	if (red_team)
	{
		// Initialising one of the players on the red team.
		player->Init(sf::Vector2f(300.0f, 400.0f), sf::Vector2f(25.0f, 75.0f), world_, ObjectID::playerOne, sf::Color::Red, 0.2f);
	}
	// Otherwise, the player is on the blue team.
	else
	{
		// Initialising one of the players on the blue team.
		player->Init(sf::Vector2f(800.0f, 400.0f), sf::Vector2f(25.0f, 75.0f), world_, ObjectID::playerTwo, sf::Color::Blue, 0.2f);
	}

	// Adding the game object to the level objects vector.
	level_objects_.push_back(player);

}

void LevelGenerator::CreateFootball(sf::Vector2f& position)
{

	// Allocating memory for the football when we need it.
	DynamicBodyRectangle* football = new DynamicBodyRectangle();

	// Initialising the dynamic body for the football.
	football->Init(position, sf::Vector2f(40.0f, 40.0f), world_, ObjectID::ball, sf::Color::White, 0.9f);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(football);

}

void LevelGenerator::Reset()
{

	// If there are objects in the level.
	if (!level_objects_.empty())
	{
		// Iterating through all of the level objects.
		for (auto& level_object : level_objects_)
		{
			// If the level object is a football.
			if (level_object->GetID() == ObjectID::ball
				|| (level_object->GetID() == ObjectID::playerOne)
				|| (level_object->GetID() == ObjectID::playerTwo))
			{
				// Casting this to a dynamic body rectangle in order to update the sprites position for level object.
				DynamicBodyRectangle* dynamic_rectangle = static_cast<DynamicBodyRectangle*>(level_object);
				dynamic_rectangle->TranslateBody(dynamic_rectangle->GetRespawnPosition().x, dynamic_rectangle->GetRespawnPosition().y);
			}
		}
	}

}

void LevelGenerator::Clear()
{

	// Destroying the fixtures that were created during the set up of the text file levels.
	// This means that there will be no random collisions in the level.
	for (std::vector<GameObject*>::iterator level_object = level_objects_.begin(); level_object != level_objects_.end(); level_object++)
	{
		(**level_object).GetBody()->DestroyFixture((**level_object).GetBody()->GetFixtureList());
		(**level_object).~GameObject();
		world_->DestroyBody((**level_object).GetBody());
	}

	// If there are objects in the level.
	if (!level_objects_.empty())
	{
		// Remove all of the objects from the level objects vector.
		level_objects_.clear();
	}

	// If there is a set of scores stored in the level.
	if (!scores_.empty())
	{
		// Clear the data for the scores.
		for (int i = 0; i < 2; i++)
		{
			delete scores_[i];
			scores_[i] = nullptr;
		}
	}

	// Resetting the finished flag.
	finished_ = false;

}

void LevelGenerator::Render(sf::RenderWindow& game_window)
{

	// If there are objects in the level.
	if (!level_objects_.empty())
	{
		// Iterating through all of the level objects.
		for (auto level_object = level_objects_.begin(); level_object != level_objects_.end(); level_object++)
		{
			// If the level object has a rectangle shape.
			if ((**level_object).IsRectangle())
			{
				// Therefore, draw the rectangle shape.
				game_window.draw((**level_object).GetRectangleShape());
			}
			// Otherwise, the level object will have a circle shape.
			else
			{
				// Draw the circle shape for the football.
				game_window.draw((**level_object).GetCircleShape());
			}
		}
	}

	// If there is a set of scores in the level.
	if (!scores_.empty())
	{
		// Iterating through all of the level scores.
		for (auto score = scores_.begin(); score != scores_.end(); score++)
		{
			// Draw the score on the screen.
			game_window.draw((**score));
		}
	}

}