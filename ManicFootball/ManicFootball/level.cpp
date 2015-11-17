#include "level.h"

Level::Level() : level_objects_(NULL),
	scores_(NULL)
{
}

Level::~Level()
{
}

void Level::Init(b2World* world, sf::Font& font, sf::Vector2f& game_screen_resolution, bool player_team, float lag_offset)
{

	// Initialising local attributes.
	finished_ = false;								// The match has not finished yet.
	red_team_score_ = 2;							// The current score of the red team.
	blue_team_score_ = 2;							// The current score of the blue team.
	previous_red_team_score_ = red_team_score_;		// The current previous score of the red team.
	previous_blue_team_score_ = blue_team_score_;	// The current previous score of the blue team.
	red_convert_ << red_team_score_;				// Places the textual representation of the red team score integer into red_convert_.
	blue_convert_ << blue_team_score_;				// Places the textual representation of the blue team score integer into blue_convert_.
	world_ = world;									// Access to the box2D world.
	font_ = &font;									// Access to the game font.
	screen_resolution_ = &game_screen_resolution;	// Access to the game resolution.
	lag_offset_ = lag_offset;						// What each networked message should take into consideration.

	// Creating the level.
	CreateGround();
	CreateWall(sf::Vector2f(0.0f, 0.0f), sf::Vector2f((screen_resolution_->x * 0.0675f), screen_resolution_->y));
	CreateWall(sf::Vector2f(0.0f, (screen_resolution_->y - (screen_resolution_->y * 0.0675f))), sf::Vector2f(screen_resolution_->x, (screen_resolution_->y * 0.0675f)));
	CreateWall(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(screen_resolution_->x, screen_resolution_->y * 0.0675f));
	CreateWall(sf::Vector2f((screen_resolution_->x - (screen_resolution_->x * 0.0675f)), 0.0f), sf::Vector2f((screen_resolution_->x * 0.0675f), screen_resolution_->y));
	CreateNets(true);
	CreateNets(false);
	CreateScoreboard();
	CreatePlayer(player_team);
	CreateOtherPlayer(player_team);
	//CreateFootball(sf::Vector2f(screen_resolution_->x * 0.25f, screen_resolution_->y * 0.25f));
	CreateFootball(sf::Vector2f(screen_resolution_->x * 0.5f, screen_resolution_->y * 0.25f));
	//CreateFootball(sf::Vector2f(screen_resolution_->x * 0.75f, screen_resolution_->y * 0.25f));

}

void Level::CreateGround()
{

	// Allocating memory for the ground when we need it.
	StaticBody* ground = new StaticBody();

	// Initialising the static body for the ground.
	ground->Init(sf::Vector2f(0.0f, (screen_resolution_->y - (screen_resolution_->y * 0.0675f)) - (screen_resolution_->y * 0.0625f)), sf::Vector2f(screen_resolution_->x, (screen_resolution_->y * 0.0625f)), world_, ObjectID::surface, sf::Color::Green, true);
	
	// Adding the game object to the level objects vector.
	level_objects_.push_back(ground);

}

void Level::CreateWall(sf::Vector2f& position, sf::Vector2f& dimension)
{

	// Allocating memory for the ground when we need it.
	StaticBody* wall = new StaticBody();

	// Initialising the static body for the ground.
	wall->Init(sf::Vector2f(position.x, position.y), sf::Vector2f(dimension.x, dimension.y), world_, ObjectID::surface, sf::Color::Black, true);
	
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

void Level::CreatePlayer(bool red_team)
{

	// Allocating memory for the player when we need it.
	Player* player = new Player();

	// If the player is on the red team.
	if (red_team)
	{
		// Initialising the player on the red team.
		player->Init(sf::Vector2f(300.0f, 200.0f), sf::Vector2f(25.0f, 75.0f), world_, red_team);
	}
	// Otherwise, the player is on the blue team.
	else
	{
		// Initialising the player on the blue team.
		player->Init(sf::Vector2f(800.0f, 200.0f), sf::Vector2f(25.0f, 75.0f), world_, red_team);
	}

	// Adding the game object to the level objects vector.
	level_objects_.push_back(player);

}

void Level::CreateOtherPlayer(bool red_team)
{

	// Allocating memory for the other player when we need it.
	DynamicBodyRectangle* other_player = new DynamicBodyRectangle();

	// If the player is on the red team.
	if (red_team)
	{
		// Initialising the dynamic body for the other player on the blue team.
		other_player->Init(sf::Vector2f(800.0f, 200.0f), sf::Vector2f(25.0f, 75.0f), world_, ObjectID::otherPlayer, sf::Color::Blue, 0.2f);
	}
	// Otherwise, the player is on the blue team.
	else
	{
		// Initialising the dynamic body for the other player on the red team.
		other_player->Init(sf::Vector2f(300.0f, 200.0f), sf::Vector2f(25.0f, 75.0f), world_, ObjectID::otherPlayer, sf::Color::Red, 0.2f);
	}

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
	football->Init(position, sf::Vector2f(40.0f, 40.0f), world_, ObjectID::ball, sf::Color::White, 0.9f);

	// Adding the game object to the level objects vector.
	level_objects_.push_back(football);

}

void Level::Reset()
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
			if ((**level_object).GetID() == ObjectID::ball
				|| ((**level_object).GetID() == ObjectID::otherPlayer))
			{
				// Casting this to a dynamic body rectangle in order to update the sprites position for level object.
				DynamicBodyRectangle* dynamic_rectangle = static_cast<DynamicBodyRectangle*>(*level_object);
				dynamic_rectangle->TranslateBody(dynamic_rectangle->GetRespawnPosition().x, dynamic_rectangle->GetRespawnPosition().y);
			}
			// Otherwise, if the object is a player.
			else if ((**level_object).GetID() == ObjectID::player)
			{
				// Casting this to a player in order to update the sprites position for level object.
				Player* player = static_cast<Player*>(*level_object);
				player->TranslateBody(player->GetRespawnPosition().x, player->GetRespawnPosition().y);
			}
		}
	}

}

void Level::UpdateTheScoreboard()
{

	// If the new red team score is greater than their previous score.
	if (red_team_score_ > previous_red_team_score_)
	{
		// Update the score for the red team.
		UpdateTheScore(red_team_score_, previous_red_team_score_, red_convert_, true);
	}
	
	// If the blue team score is greater than their previous score.
	if (blue_team_score_ > previous_blue_team_score_)
	{
		// Update the score for the blue team.
		UpdateTheScore(blue_team_score_, previous_blue_team_score_, blue_convert_, false);
	}

}

void Level::UpdateTheScore(int score, int previous_score, std::ostringstream& conversion, bool red_team)
{

	int score_index = 0;	// Which score will be updated. 0 for red and 1 for blue.

	// Set the previous team score.
	previous_score = score;

	// Clear the ostringstream and "reset" it.
	// So score numbers don't pile up.
	// E.g. 0123...
	conversion.clear();
	conversion.str("");

	// Insert the new score into the ostringstream.
	conversion << score;

	// Quick error check.
	// We don't want to try and access elements that aren't there.
	// If the score is for the red team.
	if (red_team)
	{
		// Make it the first value in the score data structure.
		score_index = 0;
	}
	// Otherwise, if the score is for the blue team.
	else
	{
		// Make if the second value in the score data structure.
		score_index = 1;
	}

	// Reset the string value for the blue team score.
	scores_[score_index]->setString(conversion.str());
	
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
		// If the contact we are currently processing contains bodies actually touching/intersecting.
		if (contact_->IsTouching())
		{
			// Get the colliding bodies.
			b2Body* body_a = contact_->GetFixtureA()->GetBody();
			b2Body* body_b = contact_->GetFixtureB()->GetBody();

			// Collision response here.
			GameObject* game_object = static_cast<GameObject*>(body_a->GetUserData());
			GameObject* game_object2 = static_cast<GameObject*>(body_b->GetUserData());

			// If a ball collides with the red team's net.
			if (game_object->GetID() == ObjectID::redNet
				&& game_object2->GetID() == ObjectID::ball)
			{
				std::cout << "The blue team have scored!" << std::endl;

				// Reset the level for the next round.
				Reset();

				// Increment the blue team's score.
				IncrementBlueTeamScore();

				// Update with the new scores.
				UpdateTheScoreboard();

				// If the blue team has reached three goals.
				if (blue_team_score_ == 3)
				{
					// The match has now finished.
					finished_ = true;
				}
			}
			// Otherwise, if the ball has collided with the blue team's net.
			else if (game_object->GetID() == ObjectID::blueNet
				&& game_object2->GetID() == ObjectID::ball)
			{
				std::cout << "The red team have scored!" << std::endl;

				// Reset the level for the next round.
				Reset();

				// Increment the red team's score.
				IncrementRedTeamScore();

				// Update with the new scores.
				UpdateTheScoreboard();

				// If the red team has reached three goals.
				if (red_team_score_ == 3)
				{
					// The match has now finished.
					finished_ = true;
				}
			}

			// Get the next contact point.
			contact_ = contact_->GetNext();
		}
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
			if ((**level_object).GetID() == ObjectID::ball
				|| ((**level_object).GetID() == ObjectID::otherPlayer))
			{
				// Casting this to a dynamic body circle in order to update the sprites position for level object.
				DynamicBodyRectangle* dynamic_rectangle = static_cast<DynamicBodyRectangle*>(*level_object);
				dynamic_rectangle->Update(dt);
			}
			// Otherwise, if the object is a player.
			else if ((**level_object).GetID() == ObjectID::player)
			{
				// Casting this to a player in order to update the sprites position for level object.
				Player* temp = static_cast<Player*>(*level_object);
				temp->Update(dt);
			}
		}
	}

}

void Level::Clear()
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
		scores_.clear();
	}

	// Resetting the finished flag.
	finished_ = false;

}

void Level::Update(float dt)
{

	HandleLevelObjects(dt);
	CollisionTest();

}