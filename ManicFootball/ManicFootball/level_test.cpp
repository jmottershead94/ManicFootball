#include "level_test.h"

LevelTest::LevelTest() : level_objects_(NULL),
scores_(NULL)
{
}

LevelTest::~LevelTest()
{
}

void LevelTest::Init(sf::Font& font, sf::Vector2f& game_screen_resolution, PhysicsEngine& physics)
{

	// Initialising local attributes.
	reset_ = false;									// The level does not need resetting right now.
	red_team_score_ = 0;							// The current score of the red team.
	blue_team_score_ = 0;							// The current score of the blue team.
	font_ = &font;									// Access to the game font.
	screen_resolution_ = &game_screen_resolution;	// Access to the game resolution.
	red_convert_ << red_team_score_;				// Places the textual representation of the red team score integer into red_convert_.
	blue_convert_ << blue_team_score_;				// Places the textual representation of the blue team score integer into blue_convert_.
	physics_ = &physics;

	// Creating the level.
	CreateGround();
	CreateWall(sf::Vector2f(0.0f, 0.0f), sf::Vector2f((screen_resolution_->x * 0.0675f), screen_resolution_->y));
	CreateWall(sf::Vector2f(0.0f, (screen_resolution_->y - (screen_resolution_->y * 0.0675f))), sf::Vector2f(screen_resolution_->x, (screen_resolution_->y * 0.0675f)));
	CreateWall(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(screen_resolution_->x, screen_resolution_->y * 0.0675f));
	CreateWall(sf::Vector2f((screen_resolution_->x - (screen_resolution_->x * 0.0675f)), 0.0f), sf::Vector2f((screen_resolution_->x * 0.0675f), screen_resolution_->y));
	CreateNets(true);
	CreateNets(false);
	CreateScoreboard();
	CreatePlayer();
	CreateOtherPlayers();
	CreateFootball(sf::Vector2f(screen_resolution_->x * 0.5f, screen_resolution_->y * 0.25f));

}

void LevelTest::CreateGround()
{

	// Allocating memory for the ground when we need it.
	GameObject* ground = new GameObject();

	// Initialising the static body for the ground.
	ground->InitPE(sf::Vector2f(0.0f, 600.0f), sf::Vector2f(screen_resolution_->x, (screen_resolution_->y * 0.125f)), ObjectID::surface, true, sf::Color::Green);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(ground);

}

void LevelTest::CreateWall(sf::Vector2f& position, sf::Vector2f& dimension)
{

	// Allocating memory for the ground when we need it.
	GameObject* wall = new GameObject();

	// Initialising the static body for the ground.
	wall->InitPE(sf::Vector2f(position.x, position.y), sf::Vector2f(dimension.x, dimension.y), ObjectID::surface, true, sf::Color::Cyan);

	// Adding the game object to the LevelTest objects vector.
	level_objects_.push_back(wall);

}

void LevelTest::CreateNets(bool left_of_the_field)
{

	// Allocating memory for the crossbar when we need it.
	GameObject* crossbar = new GameObject();

	// Allocating memory for the net when we need it.
	GameObject* net = new GameObject();

	// If the nets should be to the left of the field.
	if (left_of_the_field)
	{
		// Initialising the static body for the ground.
		crossbar->InitPE(sf::Vector2f((screen_resolution_->x * 0.0675f), (screen_resolution_->y * 0.5625f)), sf::Vector2f(screen_resolution_->x * 0.125f, screen_resolution_->y * 0.0625f), ObjectID::surface, true, sf::Color::Red);

		// Initialising the static body for the ground.
		net->InitPE(sf::Vector2f(crossbar->GetPosition().x, (crossbar->GetPosition().y + crossbar->GetDimension().y)), sf::Vector2f(screen_resolution_->x * 0.03125f, screen_resolution_->y * 0.21f),  ObjectID::redNet, true, sf::Color::Red);

		// Adding the game object to the level objects vector.
		level_objects_.push_back(crossbar);

		// Adding the game object to the level objects vector.
		level_objects_.push_back(net);
	}
	// Otherwise, the nets should be on the right side of the field.
	else
	{
		// Initialising the static body for the ground.
		crossbar->InitPE(sf::Vector2f((screen_resolution_->x - (screen_resolution_->x * 0.0675f)), (screen_resolution_->y * 0.5625f)), sf::Vector2f(-1.0f * (screen_resolution_->x * 0.125f), (screen_resolution_->y * 0.0625f)), ObjectID::surface, true, sf::Color::Blue);

		// Initialising the static body for the ground.
		net->InitPE(sf::Vector2f((screen_resolution_->x - (screen_resolution_->x * 0.0675f) - (screen_resolution_->x * 0.03125f)), (crossbar->GetPosition().y + crossbar->GetDimension().y)), sf::Vector2f((screen_resolution_->x * 0.03125f), screen_resolution_->y * 0.21f), ObjectID::blueNet, true, sf::Color::Blue);

		// Adding the game object to the level objects vector.
		level_objects_.push_back(crossbar);

		// Adding the game object to the level objects vector.
		level_objects_.push_back(net);
	}


}

void LevelTest::CreateScoreboard()
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

void LevelTest::CreatePlayer()
{

	// Allocating memory for the player when we need it.
	PlayerTest* player = new PlayerTest();

	// Initialising the player on the red team.
	player->Init(sf::Vector2f(300.0f, 200.0f), sf::Vector2f(25.0f, 75.0f), true, *physics_);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(player);

}

void LevelTest::CreateOtherPlayers()
{

	// Allocating memory for the other player when we need it.
	GameObject* other_player = new GameObject();

	// Initialising the dynamic body for the other player on the red team.
	other_player->InitPE(sf::Vector2f(800.0f, 200.0f), sf::Vector2f(25.0f, 75.0f), ObjectID::otherPlayer, true, sf::Color::Blue);

	// Adding the game object to the LevelTest objects vector.
	level_objects_.push_back(other_player);

}

void LevelTest::CreateFootball(sf::Vector2f& position)
{

	// Allocating memory for the football when we need it.
	GameObject* football = new GameObject();

	// Initialising the dynamic body for the football.
	football->InitPE(position, sf::Vector2f(0.0f, 0.0f), ObjectID::ball, false, sf::Color::White);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(football);

}

void LevelTest::Reset()
{

}

void LevelTest::UpdateScoreboard()
{

	red_convert_ << red_team_score_;				// Places the textual representation of the red team score integer into red_convert_.
	blue_convert_ << blue_team_score_;				// Places the textual representation of the blue team score integer into blue_convert_.

	// If there are elements in the scores vector.
	if (!scores_.empty())
	{
		// Update the score strings with the new integers.
		scores_[0]->setString(red_convert_.str());
		scores_[1]->setString(blue_convert_.str());
	}

}

void LevelTest::RemoveObjects()
{
	// If there are objects in the level.
	if (!level_objects_.empty())
	{
		// Iterating through all of the level objects.
		for (auto level_object = level_objects_.begin(); level_object != level_objects_.end(); level_object++)
		{
			// If an object needs to be removed from the level.
			if ((**level_object).NeedsRemoving())
			{
				// Remove the object from the vector.
				level_objects_.erase(level_object);
			}
		}
	}

}

void LevelTest::CollisionTest(float dt)
{

	// If there are objects in the level.
	if (!level_objects_.empty())
	{
		// Iterating through all of the level objects.
		for (auto level_object_a = level_objects_.begin(); level_object_a != level_objects_.end(); level_object_a++)
		{
			for (auto level_object_b = level_objects_.begin(); level_object_b != level_objects_.end(); level_object_b++)
			{
				if (physics_->BoundingObjectCollider((**level_object_a), (**level_object_b), dt))
				{
					// Do game specific collision response here.
					// Scoring goals etc.
				}
			}
		}
	}

}

void LevelTest::HandleLevelObjects(float dt)
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
				physics_->Update((**level_object), dt);
			}
			// Otherwise, if the object is a player.
			else if ((**level_object).GetID() == ObjectID::player)
			{
				// Casting this to a player in order to update the sprites position for LevelTest object.
				PlayerTest* temp = static_cast<PlayerTest*>(*level_object);
				temp->Update(dt);
			}
			// Otherwise, the object is another player.
			else if ((**level_object).GetID() == ObjectID::otherPlayer)
			{
				// Casting this to a dynamic body rectangle in order to update the sprites position for level object.
				physics_->Update((**level_object), dt);
			}
		}
	}

}

void LevelTest::Clear()
{

}

void LevelTest::Update(float dt)
{

	HandleLevelObjects(dt);
	CollisionTest(dt);

}