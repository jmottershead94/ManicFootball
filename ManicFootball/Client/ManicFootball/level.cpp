#include "level.h"

Level::Level() : world_(nullptr),
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
	PositionUpdate position_update;

	// If the data we have received is input data.
	if (network_->ReceivedInputMessageFromServer())
	{
		// Place the input data into the input struct for the other player.
		if (network_->GetData() >> object.GetInput())
		{
			// Apply the input to the other player.
			ApplyPlayerInput(object, dt);

			// Just update the positions.
			// Filling the position update every frame.
			position_update.x = object.GetPosition().x;
			position_update.y = object.GetPosition().y;
			position_update.time = network_->GetClock().getElapsedTime().asMilliseconds();

			// Place the positions in the vector of positions for interpolation/prediction.
			other_player_.UpdateVectors(position_update.x, position_update.y, position_update.time);
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
	// Otherwise, if we have received some position updates.
	else if (network_->ReceivedDeadReckoningMessageFromServer())
	{
		// See if we can place the data into a position update struct.
		if (network_->GetData() >> position_update)
		{
			// Place the positions in the vector of positions for interpolation/prediction.
			/*other_player_x_.push_back(position_update.x);
			other_player_y_.push_back(position_update.y);
			other_player_position_time_.push_back(position_update.time);*/

			other_player_.UpdateVectors(position_update.x, position_update.y, position_update.time);
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

	// If we have 16 x and y coordinates.
	if ((other_player_.GetXPositions().size() == 16) && (other_player_.GetYPositions().size() == 16))
	{
		PositionUpdate position_update;

		// Place in the points for the other player x position and the time they were received at.
		other_player_.SetXPoints();

		// Place in the points for the other player y position and the time they were received at.
		other_player_.SetYPoints();

		for (auto& object : level_generator_.GetLevelObjects())
		{
			if (object->GetID() == ObjectID::otherPlayer)
			{
				// This should interpolate/predict the next however many points.
				// Place in a check to make sure it doesn't stray too far.
				// If the absolute value of the x position minus the previous x position is less than the network difference in x threshold.
				if (abs(other_player_.GetInterpolationX()(network_->GetClock().getElapsedTime().asMilliseconds()) - object->GetPosition().x) < network_->GetThreshold())
				{
					// If the absolute value of the y position minus the previous y position is less than the network difference in y threshold.
					if (abs(other_player_.GetInterpolationY()(network_->GetClock().getElapsedTime().asMilliseconds()) - object->GetPosition().y) < network_->GetThreshold())
					{
						//std::cout << "We are interpolating." << std::endl;

						// We can move the body through interpolation.
						object->TranslateBody(other_player_.GetInterpolationX()(network_->GetClock().getElapsedTime().asMilliseconds()), other_player_.GetInterpolationY()(network_->GetClock().getElapsedTime().asMilliseconds()));
					
						// Update the struct values.
						position_update.x = other_player_.GetInterpolationX()(network_->GetClock().getElapsedTime().asMilliseconds());
						position_update.y = other_player_.GetInterpolationY()(network_->GetClock().getElapsedTime().asMilliseconds());
						position_update.time = network_->GetClock().getElapsedTime().asMilliseconds();

						// Send the updated struct to the server.
						network_->SendDeadReckoningMessageToServer(position_update);
					}
				}		
			}
		}

		other_player_.ClearVectors();
	}

}

void Level::Update(float dt)
{

	CorrectPositions();
	HandleLevelObjects(dt);
	CollisionTest();

}