#include "level.h"

Level::Level() :	world_(nullptr),
	font_(nullptr),
	screen_resolution_(nullptr),
	network_(nullptr)
{
}

Level::~Level()
{
}

void Level::Init(b2World* world, sf::Font& font, sf::Vector2f& game_screen_resolution, Network& network)
{

	// Initialising local attributes.
	world_ = world;									// Access to the box2D world.
	font_ = &font;									// Access to the game font.
	screen_resolution_ = &game_screen_resolution;	// Access to the game resolution.
	network_ = &network;							// Access to the game network.
	lag_offset_ = network_->GetLagOffset();			// What each networked message should take into consideration.

	// Creating the level.
	level_generator_.Init(world, font, game_screen_resolution, network);

	// Starting the game clock for the player.
	clock_.restart().asMilliseconds();

}

void Level::UpdateTheScoreboard()
{

	// If the new red team score is greater than their previous score.
	if (level_generator_.GetRedTeamScore() > level_generator_.GetPreviousRedTeamScore())
	{
		// Update the score for the red team.
		UpdateTheScore(level_generator_.GetRedTeamScore(), level_generator_.GetPreviousRedTeamScore(), level_generator_.red_convert_, true);
	}

	// If the blue team score is greater than their previous score.
	if (level_generator_.GetBlueTeamScore() > level_generator_.GetPreviousBlueTeamScore())
	{
		// Update the score for the blue team.
		UpdateTheScore(level_generator_.GetBlueTeamScore(), level_generator_.GetPreviousBlueTeamScore(), level_generator_.blue_convert_, false);
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
	level_generator_.GetScoresText()[score_index]->setString(conversion.str());
	
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
				level_generator_.Reset();

				// Increment the blue team's score.
				level_generator_.IncrementBlueTeamScore();

				// Update with the new scores.
				UpdateTheScoreboard();

				// If the blue team has reached three goals.
				if (level_generator_.GetBlueTeamScore() == 3)
				{
					// The match has now finished.
					level_generator_.SetFinished(true);
				}
			}
			// Otherwise, if the ball has collided with the blue team's net.
			else if (game_object->GetID() == ObjectID::blueNet
					&& game_object2->GetID() == ObjectID::ball)
			{
				std::cout << "The red team have scored!" << std::endl;

				// Reset the level for the next round.
				level_generator_.Reset();

				// Increment the red team's score.
				level_generator_.IncrementRedTeamScore();

				// Update with the new scores.
				UpdateTheScoreboard();

				// If the red team has reached three goals.
				if (level_generator_.GetRedTeamScore() == 3)
				{
					// The match has now finished.
					level_generator_.SetFinished(true);
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
	if (!level_generator_.GetLevelObjects().empty())
	{
		// Iterating through all of the level objects.
		for (auto& level_object : level_generator_.GetLevelObjects())
		{
			// If the level object is a football.
			if (level_object->GetID() == ObjectID::ball)
			{
				// Casting this to a dynamic body rectangle in order to update the sprites position for level object.
				DynamicBodyRectangle* dynamic_rectangle = static_cast<DynamicBodyRectangle*>(level_object);
				dynamic_rectangle->Update(dt);
			}
			else if (level_object->GetID() == ObjectID::otherPlayer)
			{
				// Casting this to a dynamic body rectangle in order to update the sprites position for level object.
				DynamicBodyRectangle* dynamic_rectangle = static_cast<DynamicBodyRectangle*>(level_object);
				
				// Provide the appropriate data response for the player, depending on the package that they have received.
				DataResponse(network_->GetData(), *dynamic_rectangle, dt);
				
				// Update the other player.
				dynamic_rectangle->Update(dt);
			}
			// Otherwise, if the object is a player.
			else if (level_object->GetID() == ObjectID::player)
			{
				// Casting this to a player in order to update the sprites position for level object.
				Player* temp = static_cast<Player*>(level_object);
				
				// Sending the current input message data to the server.
				network_->SendInputMessageToServer(temp->GetInput());

				// Updating the player.
				temp->Update(dt);
			}
		}
	}

}

void Level::DataResponse(sf::Packet& data, DynamicBodyRectangle& object, float dt)
{

	// Add in additional structs here for any further information.
	FinishMessage finish_message;

	// If the data we have received is input data.
	if (network_->ReceivedInputMessageFromServer())
	{
		// Place the input data into the input struct for the other player.
		if (network_->GetData() >> object.GetInput())
		{
			// Apply the input to the other player.
			ApplyPlayerInput(object, dt);
		}
	}
	// Otherwise, if we have received finish message data.
	else if (network_->ReceivedFinishMessageFromServer())
	{
		// Place the finish message data into the finish message struct for the other player.
		if (network_->GetData() >> finish_message)
		{
			// Finish the match.
			level_generator_.SetFinished(true);
		}
	}

}

void Level::ApplyPlayerInput(DynamicBodyRectangle& player, float dt)
{

	// If player one pressed up.
	if (player.GetInput().up)
	{
		player.GetBody()->SetAwake(true);
		player.GetBody()->ApplyLinearImpulse(b2Vec2(0.0f, player.GetMovementForce().y * dt), player.GetBody()->GetWorldCenter(), player.GetBody()->IsAwake());
	}

	// Move the body to the right.
	if (player.GetInput().right)
	{
		player.GetBody()->SetAwake(true);
		player.GetBody()->ApplyLinearImpulse(b2Vec2((player.GetMovementForce().x * dt), 0.0f), player.GetBody()->GetWorldCenter(), player.GetBody()->IsAwake());
	}

	// Move the body to the left.
	if (player.GetInput().left)
	{
		player.GetBody()->SetAwake(true);
		player.GetBody()->ApplyLinearImpulse(b2Vec2(((player.GetMovementForce().x * -1.0f) * dt), 0.0f), player.GetBody()->GetWorldCenter(), player.GetBody()->IsAwake());
	}

}

void Level::CorrectPositions()
{

	//// If we have received a position correction message from the server.
	//if (network_->ReceivedPositionMessageFromServer())
	//{
	//	// Setting up the correction struct.
	//	PositionCorrection correct_position;

	//	// Place the data into the struct we just made.
	//	network_->GetData() >> correct_position;

	//	// If there are objects in the level.
	//	if (!level_objects_.empty())
	//	{
	//		// Iterating through all of the level objects.
	//		for (auto& level_object : level_objects_)
	//		{
	//			if (((level_object->GetID() == correct_position.object_id) && (correct_position.object_id == ObjectID::player))
	//				|| ((level_object->GetID() == correct_position.object_id) && (correct_position.object_id == ObjectID::otherPlayer))
	//				|| ((level_object->GetID() == correct_position.object_id) && (correct_position.object_id == ObjectID::ball)))
	//			{
	//				level_object->TranslateBody(correct_position.x, correct_position.y);
	//			}
	//		}
	//	}
	//}

}

void Level::UpdatePositions()
{

	PositionUpdate player;
	//PositionUpdate otherPlayer;
	//PositionUpdate ball;

	// If there are objects in the level.
	if (!level_generator_.GetLevelObjects().empty())
	{
		// Iterating through all of the level objects.
		for (auto& level_object : level_generator_.GetLevelObjects())
		{
			// If the level object is the first player.
			if (level_object->GetID() == ObjectID::player)
			{
				// Update the struct with player coordinates.
				player.x = level_object->GetPosition().x;
				player.y = level_object->GetPosition().y;
				player.time = clock_.getElapsedTime().asMilliseconds();

				// Send the position information to the server.
				network_->SendPositionMessageToServer(player);
			}
			/*else if (level_object->GetID() == ObjectID::ball)
			{
				ball.x = level_object->GetPosition().x;
				ball.y = level_object->GetPosition().y;
				ball.time = clock_.getElapsedTime().asMilliseconds();
			}*/
		}
	}
	

}

void Level::Update(float dt)
{

	/*if ((int)clock_.getElapsedTime().asSeconds() % 5 == 0)
	{
		CorrectPositions();
	}*/

	HandleLevelObjects(dt);
	CollisionTest();

}