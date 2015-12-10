// Include header file here.
#include "level.h"

//////////////////////////////////////////////////////////
//======================================================//
//					Constructor							//
//======================================================//
// This will initialise any pointers we have to null.	//
//////////////////////////////////////////////////////////
Level::Level() : network_(nullptr)
{
}

//////////////////////////////////////////////////////////
//======================================================//
//					Destructor							//
//======================================================//
//////////////////////////////////////////////////////////
Level::~Level()
{
}

//////////////////////////////////////////////////////////
//======================================================//
//						Init							//
//======================================================//
// This will intialise the game level and build the		//
// level that we want.									//
//////////////////////////////////////////////////////////
void Level::Init(b2World* world, sf::Font& font, sf::Vector2f& game_screen_resolution, Network& network)
{

	// Initialising local attributes.
	network_ = &network;							// Access to the game network.

	// Creating the level.
	level_generator_.Init(world, font, game_screen_resolution, network);
	
}

//////////////////////////////////////////////////////////
//======================================================//
//					UpdateTheScoreboard					//
//======================================================//
// This will update the current score on the score if	//
// we have any new scores.								//
//////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////
//======================================================//
//					UpdateTheScore						//
//======================================================//
// This will update the current score.					//
//////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////
//======================================================//
//					HandleLevelObjects					//
//======================================================//
// This will update all of the objects in our level.	//
// And handle any approriate responses.					//
//////////////////////////////////////////////////////////
void Level::HandleLevelObjects(float dt)
{
	
	// If there are objects in the level.
	if (!level_generator_.GetLevelObjects().empty())
	{
		// Iterating through all of the level objects.
		for (auto& level_object : level_generator_.GetLevelObjects())
		{
			// If the level object is a player.
			if (level_object->GetID() == ObjectID::player)
			{
				// Casting this to a player in order to update the sprites position for level object.
				Player* player_temp = static_cast<Player*>(level_object);

				// Sending the current input message data to the server.
				network_->SendInputMessageToServer(player_temp->GetInput());

				// Updating the player.
				player_temp->Update(dt);
			}
			// Otherwise, if the level object is the other player.
			else if (level_object->GetID() == ObjectID::otherPlayer)
			{
				// Casting this to a dynamic body rectangle in order to update the sprites position for level object.
				DynamicBodyRectangle* dynamic_rectangle = static_cast<DynamicBodyRectangle*>(level_object);
				
				//if (!other_player_.IsInterpolating())
				//{
					// Provide the appropriate data response for the player, depending on the package that they have received.
					DataResponse(network_->GetData(), *dynamic_rectangle, dt);
				//}

				// Update the other player.
				dynamic_rectangle->Update(dt);
			}
			// Otherwise, if the level object is a football.
			else if (level_object->GetID() == ObjectID::ball)
			{
				// Casting this to a dynamic body rectangle in order to update the sprites position for level object.
				DynamicBodyRectangle* dynamic_rectangle = static_cast<DynamicBodyRectangle*>(level_object);

				// Creating a server update message.
				ServerUpdate server_update;

				// If we have received an update from the server.
				if (network_->ReceivedServerUpdateMessageFromServer())
				{
					// See if we can place the data into a server update struct.
					if (network_->GetData() >> server_update)
					{
						// Checking to see if we have any new scores from the server.
						if (server_update.red_score > level_generator_.GetRedTeamScore())
						{
							UpdateTheScore(server_update.red_score, level_generator_.GetPreviousRedTeamScore(), level_generator_.red_convert_, true);
						}

						if (server_update.blue_score > level_generator_.GetBlueTeamScore())
						{
							UpdateTheScore(server_update.blue_score, level_generator_.GetPreviousBlueTeamScore(), level_generator_.blue_convert_, false);
						}

						// Place the ball into the correct position.
						dynamic_rectangle->TranslateBody(server_update.x, server_update.y);
					}
				}

				// If we have reached the maximum score limit.
				if ((server_update.red_score == 3) || (server_update.blue_score == 3))
				{
					// Notify the states.
					level_generator_.SetFinished(true);
				}

				// Update the ball.
				dynamic_rectangle->Update(dt);
			}
		}
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//					Data Response						//
//======================================================//
// This will provide the approriate response for the	//
// other player we have displayed on our screen.		//
//////////////////////////////////////////////////////////
void Level::DataResponse(sf::Packet& data, DynamicBodyRectangle& object, float dt)
{

	// Add in additional structs here for any required further information.
	ServerUpdate update;
	
	// If the data we have received is input data.
	if (network_->ReceivedInputMessageFromServer())
	{
		// Place the input data into the input struct for the other player.
		if (network_->GetData() >> object.GetInput())
		{
			// Apply the input to the other player.
			ApplyPlayerInput(object, dt);
			
			// Store the positions of the other player.
			update.x = (object.GetPosition().x + (object.GetBody()->GetAngularVelocity() * dt));
			update.y = (object.GetPosition().y + (object.GetBody()->GetAngularVelocity() * dt));
			update.time = (object.GetInput().time + network_->GetLagOffset());

			// Place the positions in the vector of positions for interpolation/prediction.
			other_player_.UpdateVectors(update.x, update.y, update.time);
		}
	}
	
}

//////////////////////////////////////////////////////////
//======================================================//
//					ApplyPlayerInput					//
//======================================================//
// This will apply the commands sent to us by the other	//
// player to move our representation of the other		//
// player.												//
//////////////////////////////////////////////////////////
void Level::ApplyPlayerInput(DynamicBodyRectangle& player, float dt)
{

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

//////////////////////////////////////////////////////////
//======================================================//
//					CorrectPositions					//
//======================================================//
// This will interpolate the positions for the other	//
// player on our screen.								//
//////////////////////////////////////////////////////////
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
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
// This will interpolate and handle object responses	//
// every frame.											//
//////////////////////////////////////////////////////////
void Level::Update(float dt)
{
	
	// Interpolate the other player.
	CorrectPositions(dt);

	// Handle all of our level objects.
	HandleLevelObjects(dt);
	
}