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
				
				if (network_->ReceivedDeadReckoningMessageFromServer())
				{
					PositionUpdate position_update;

					// See if we can place the data into a position update struct.
					if (network_->GetData() >> position_update)
					{
						// We need to place the ball in the server position.
						if (position_update.id == ObjectID::ball)
						{
							// Place the ball into the correct position.
							dynamic_rectangle->TranslateBody(position_update.x, position_update.y);
						}
						// We need to apply the position update else where!
						else
						{
							network_->GetData() << position_update;
						}
					}
				}
				
				dynamic_rectangle->Update(dt);
			}
			else if (level_object->GetID() == ObjectID::otherPlayer)
			{
				// Casting this to a dynamic body rectangle in order to update the sprites position for level object.
				DynamicBodyRectangle* dynamic_rectangle = static_cast<DynamicBodyRectangle*>(level_object);
				
				// If we are not currently interpolating the other player's position.
				if (!other_player_.IsInterpolating())
				{
					// Provide the appropriate data response for the player, depending on the package that they have received.
					DataResponse(network_->GetData(), *dynamic_rectangle, dt);
				}

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

				//// If we have received a finish message from the server.
				//if (network_->ReceivedFinishMessageFromServer())
				//{
				//	FinishMessage finish_message;

				//	// And if we can place the data into a finish message struct.
				//	if (network_->GetData() >> finish_message)
				//	{
				//		// Finish the level.
				//		level_generator_.SetFinished(finish_message.finished);
				//	}
				//}
			}
		}
	}

}

void Level::DataResponse(sf::Packet& data, DynamicBodyRectangle& object, float dt)
{

	// Add in additional structs here for any further information.
	FinishMessage finish_message;
	PositionUpdate position_update, player_update;
	
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
			position_update.x = (object.GetPosition().x + (object.GetBody()->GetAngularVelocity() * dt));
			position_update.y = (object.GetPosition().y + (object.GetBody()->GetAngularVelocity() * dt));
			position_update.time = (object.GetInput().time + network_->GetLagOffset());

			// Place the positions in the vector of positions for interpolation/prediction.
			other_player_.UpdateVectors(position_update.x, position_update.y, position_update.time);
		}
	}
	//// Otherwise, if we have received finish message data.
	//else if (network_->ReceivedFinishMessageFromServer())
	//{
	//	// Place the finish message data into the finish message struct for the other player.
	//	if (network_->GetData() >> finish_message)
	//	{
	//		// Finish the match.
	//		level_generator_.SetFinished(finish_message.finished);
	//	}
	//}
	//// Otherwise, if we have received some position updates.
	//else if (network_->ReceivedDeadReckoningMessageFromServer())
	//{
	//	// See if we can place the data into a position update struct.
	//	if (network_->GetData() >> player_update)
	//	{
	//		// If we are updating the our player.
	//		if (player_update.id == ObjectID::player)
	//		{
	//			player_update.time += network_->GetLagOffset();

	//			// Move the player to the server positions.
	//			object.TranslateBody(player_update.x, player_update.y);
	//			//other_player_.UpdateVectors(player_update.x, player_update.y, player_update.time);
	//		}
	//		else
	//		{
	//			network_->GetData() << player_update;
	//		}
	//	}
	//}
	
}

void Level::ApplyPlayerInput(DynamicBodyRectangle& player, float dt)
{
	//PositionUpdate position_update;

	// Move the body up.
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

void Level::CorrectPositions(float dt)
{

	// Iterate through the level objects.
	for (auto& object : level_generator_.GetLevelObjects())
	{
		// If the object is the other player.
		if (object->GetID() == ObjectID::otherPlayer)
		{
			// Casting this to a dynamic body rectangle in order to update the sprites position for level object.
			DynamicBodyRectangle* dynamic_rectangle = static_cast<DynamicBodyRectangle*>(object);

			// Interpolate the other player.
			other_player_.Interpolate(*dynamic_rectangle, *network_, dt);
		}
		//// If the object is a ball.
		//else if (object->GetID() == ObjectID::ball)
		//{
		//	// Interpolate the ball.
		//	ball_.Calculate(*object, *network_);
		//}
	}

}

void Level::Update(float dt)
{

	//// If we are not currently interpolating the other player's position.
	//if (!other_player_.IsInterpolating())
	//{
	//	// Provide the appropriate data response for the player, depending on the package that they have received.
	//	DataResponse(network_->GetData(), *dynamic_rectangle, dt);
	//}

	CorrectPositions(dt);
	HandleLevelObjects(dt);
	//CollisionTest();

}