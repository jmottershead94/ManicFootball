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
	CreateWall(sf::Vector2f(0.0f, 0.0f), sf::Vector2f((screen_resolution_->x * 0.0675f), screen_resolution_->y));
	CreateWall(sf::Vector2f(0.0f, (screen_resolution_->y - (screen_resolution_->y * 0.0675f))), sf::Vector2f(screen_resolution_->x, (screen_resolution_->y * 0.0675f)));
	CreateWall(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(screen_resolution_->x, screen_resolution_->y * 0.0675f));
	CreateWall(sf::Vector2f((screen_resolution_->x - (screen_resolution_->x * 0.0675f)), 0.0f), sf::Vector2f((screen_resolution_->x * 0.0675f), screen_resolution_->y));
	CreateNets(true);
	CreateNets(false);
	CreateScoreboard();
	CreatePlayer();
	CreateOtherPlayers();
	//CreateFootball(sf::Vector2f(screen_resolution_->x * 0.25f, screen_resolution_->y * 0.25f));
	CreateFootball(sf::Vector2f(screen_resolution_->x * 0.5f, screen_resolution_->y * 0.25f));
	//CreateFootball(sf::Vector2f(screen_resolution_->x * 0.75f, screen_resolution_->y * 0.25f));

}

void Level::CreateGround()
{

	// Allocating memory for the ground when we need it.
	StaticBody* ground = new StaticBody();

	// Initialising the static body for the ground.
	ground->Init(sf::Vector2f(0.0f, 600.0f), sf::Vector2f(screen_resolution_->x, (screen_resolution_->y * 0.125f)), world_, ObjectID::surface, sf::Color::Green);
	
	// Adding the game object to the level objects vector.
	level_objects_.push_back(ground);

}

void Level::CreateWall(sf::Vector2f& position, sf::Vector2f& dimension)
{

	// Allocating memory for the ground when we need it.
	StaticBody* wall = new StaticBody();

	// Initialising the static body for the ground.
	wall->Init(sf::Vector2f(position.x, position.y), sf::Vector2f(dimension.x, dimension.y), world_, ObjectID::surface, sf::Color::Cyan);
	
	// Adding the game object to the level objects vector.
	level_objects_.push_back(wall);

}

void Level::CreateNets(bool left_of_the_field)
{

	// Allocating memory for the crossbar when we need it.
	StaticBody* crossbar = new StaticBody();

	// Allocating memory for the net when we need it.
	StaticBody* net = new StaticBody();

	// If the nets should be to the left of the field.
	if (left_of_the_field)
	{
		// Initialising the static body for the ground.
		crossbar->Init(sf::Vector2f((screen_resolution_->x * 0.0675f), (screen_resolution_->y * 0.5625f)), sf::Vector2f(screen_resolution_->x * 0.125f, screen_resolution_->y * 0.0625f), world_, ObjectID::surface, sf::Color::Red);

		// Initialising the static body for the ground.
		net->Init(sf::Vector2f(crossbar->GetPosition().x, (crossbar->GetPosition().y + crossbar->GetDimension().y)), sf::Vector2f(screen_resolution_->x * 0.03125f, screen_resolution_->y * 0.21f), world_, ObjectID::redNet, sf::Color::Red);

		// Adding the game object to the level objects vector.
		level_objects_.push_back(crossbar);
		
		// Adding the game object to the level objects vector.
		level_objects_.push_back(net);
	}
	// Otherwise, the nets should be on the right side of the field.
	else
	{
		// Initialising the static body for the ground.
		crossbar->Init(sf::Vector2f((screen_resolution_->x - (screen_resolution_->x * 0.0675f)), (screen_resolution_->y * 0.5625f)), sf::Vector2f(-1.0f * (screen_resolution_->x * 0.125f), (screen_resolution_->y * 0.0625f)), world_, ObjectID::surface, sf::Color::Blue);

		// Initialising the static body for the ground.
		net->Init(sf::Vector2f((screen_resolution_->x - (screen_resolution_->x * 0.0675f) - (screen_resolution_->x * 0.03125f)), (crossbar->GetPosition().y + crossbar->GetDimension().y)), sf::Vector2f((screen_resolution_->x * 0.03125f), screen_resolution_->y * 0.21f), world_, ObjectID::blueNet, sf::Color::Blue);

		// Adding the game object to the level objects vector.
		level_objects_.push_back(crossbar);

		// Adding the game object to the level objects vector.
		level_objects_.push_back(net);
	}


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
	player->Init(sf::Vector2f(300.0f, 200.0f), sf::Vector2f(25.0f, 75.0f), world_, true);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(player);

}

void Level::CreateOtherPlayers()
{

	// Allocating memory for the other player when we need it.
	DynamicBodyRectangle* other_player = new DynamicBodyRectangle();

	// Initialising the dynamic body for the other player on the red team.
	other_player->Init(sf::Vector2f(800.0f, 200.0f), sf::Vector2f(25.0f, 75.0f), world_, ObjectID::otherPlayer, sf::Color::Blue, 0.2f);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(other_player);

}

void Level::CreateFootball(sf::Vector2f& position)
{

	//// Allocating memory for the football when we need it.
	//DynamicBodyCircle* football = new DynamicBodyCircle();

	//// Initialising the dynamic body for the football.
	//football->Init(position, 30.0f, world_, ObjectID::ball, sf::Color::White);

	//// Adding the game object to the level objects vector.
	//level_objects_.push_back(football);

	// Allocating memory for the football when we need it.
	DynamicBodyRectangle* football = new DynamicBodyRectangle();

	// Initialising the dynamic body for the football.
	football->Init(position, sf::Vector2f(50.0f, 50.0f), world_, ObjectID::ball, sf::Color::White, 0.9f);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(football);

}

void Level::Reset()
{

}

void Level::UpdateScoreboard()
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

void Level::RemoveObjects()
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

void Level::CheckGoal()
{
	// If there are objects in the level.
	if (!level_objects_.empty())
	{
		// Iterating through all of the level objects.
		for (auto level_object = level_objects_.begin(); level_object != level_objects_.end(); level_object++)
		{
			if ((**level_object).GetID() == ObjectID::ball)
			{

				if ((**level_object).GetPosition().x < )
			}
		}
	}

}

void Level::CollisionTest()
{

	// Get the head of the contact list.
	b2Contact* contact_ = world_->GetContactList();

	// Get the contact count.
	int contact_count = world_->GetContactCount();
	
	// Cycle through the contacts.
	for (int contact_num = 0; contact_num < contact_count; contact_num++)
	{
		// Get the colliding bodies.
		b2Body* body_a = contact_->GetFixtureA()->GetBody();
		b2Body* body_b = contact_->GetFixtureB()->GetBody();

		// Collision response here.
		GameObject* game_object_ = static_cast<GameObject*>(body_a->GetUserData());
		GameObject* game_object2_ = static_cast<GameObject*>(body_b->GetUserData());

		// If a ball collides with the red team's net.
		if (game_object_->GetID() == ObjectID::ball
			&& game_object2_->GetID() == ObjectID::redNet)
		{
			// Remove the ball from the field.
			game_object_->SetRemove(true);
			game_object_->GetCircleShape().~CircleShape();
			game_object_->GetBody()->DestroyFixture(game_object_->GetBody()->GetFixtureList());

			// Increment the blue team's score.
			IncrementBlueTeamScore();

			std::cout << "Blue team have scored a goal! Blue: " << blue_team_score_ << std::endl;

			// Update with the new scores.
			UpdateScoreboard();
		}
		// Otherwise, if the ball has collided with the blue team's net.
		else if (game_object_->GetID() == ObjectID::ball
			&& game_object2_->GetID() == ObjectID::blueNet)
		{
			// Remove the ball from the field.
			game_object_->SetRemove(true);
			game_object_->GetCircleShape().~CircleShape();
			game_object_->GetBody()->DestroyFixture(game_object_->GetBody()->GetFixtureList());

			// Increment the red team's score.
			IncrementRedTeamScore();

			std::cout << "Red team have scored a goal! Red: " << red_team_score_ << std::endl;

			// Update with the new scores.
			UpdateScoreboard();
		}

		// Get the next contact point.
		contact_ = contact_->GetNext();
	}

}

void Level::HandleLevelObjects(float dt)
{
	
	// If there are objects in the level.
	if (!level_objects_.empty())
	{
		// Iterating through all of the level objects.
		for (auto level_object = level_objects_.begin(); level_object != level_objects_.end(); level_object++)
		{
			//// If the level object is a football.
			//if ((**level_object).GetID() == ObjectID::ball)
			//{
			//	// Casting this to a dynamic body circle in order to update the sprites position for level object.
			//	DynamicBodyCircle* temp = static_cast<DynamicBodyCircle*>(*level_object);
			//	temp->Update(dt);
			//}
			// If the level object is a football.
			if ((**level_object).GetID() == ObjectID::ball)
			{
				// Casting this to a dynamic body circle in order to update the sprites position for level object.
				DynamicBodyRectangle* temp = static_cast<DynamicBodyRectangle*>(*level_object);
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
	CollisionTest();

}