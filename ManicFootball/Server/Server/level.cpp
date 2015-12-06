// Include header file here.
#include "level.h"

//////////////////////////////////////////////////////////
//======================================================//
//					Constructor							//
//======================================================//
// This will initialise any pointers we have to null.	//
//////////////////////////////////////////////////////////
Level::Level() : world_(nullptr),
	clock_(nullptr),
	network_(nullptr)
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
void Level::Init(b2World* world, sf::Font& font, sf::Vector2f& game_screen_resolution, Network& network, sf::Clock& game_clock)
{

	// Initialising local attributes.
	world_ = world;									// Access to the box2D world.
	clock_ = &game_clock;							// Access to the game clock.
	network_ = &network;							// Access to the game network.
	
	// Creating the level.
	level_generator_.Init(world, font, game_screen_resolution);
	
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
//					CollisionTest						//
//======================================================//
// This will test for any collisions in our level, here	//
// we can check if collisions are happening between two	//
// specific objects, and provide a collision response.	//
// In our case, we provide a goal response when the		//
// ball collides with one of the nets.					//
//////////////////////////////////////////////////////////
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
			}

			// Get the next contact point.
			contact_ = contact_->GetNext();
		}
	}

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
			// If the level object is player one.
			if (level_object->GetID() == ObjectID::playerOne)
			{
				// Casting this to a dynamic body rectangle in order to update the sprites position for level object.
				DynamicBodyRectangle* player_one = static_cast<DynamicBodyRectangle*>(level_object);

				// Check to see if we have received any data for player one.
				if (network_->ReceivedData(*network_->GetClientSockets()[0], network_->GetData()))
				{
					// Provide the appropriate data response for the other client, depending on what data we need to send.
					DataResponse(*network_->GetClientSockets()[1], network_->GetData(), *player_one, dt);
				}

				player_one->Update(dt);
			}
			// Otherwise, if the level object is player two.
			else if (level_object->GetID() == ObjectID::playerTwo)
			{
				// Casting this to a dynamic body rectangle in order to update the sprites position for level object.
				DynamicBodyRectangle* player_two = static_cast<DynamicBodyRectangle*>(level_object);

				// Check to see if we have received any data for player two.
				if (network_->ReceivedData(*network_->GetClientSockets()[1], network_->GetData()))
				{
					// Provide the appropriate data response for the other client, depending on what data we need to send.
					DataResponse(*network_->GetClientSockets()[0], network_->GetData(), *player_two, dt);
				}

				player_two->Update(dt);
			}
			// Otherwise, if the level object is a ball.
			else if (level_object->GetID() == ObjectID::ball)
			{				
				// Casting this to a dynamic body rectangle in order to update the sprites position for level object.
				DynamicBodyRectangle* football = static_cast<DynamicBodyRectangle*>(level_object);

				// Iterating through all of our clients.
				for (auto& socket : network_->GetClientSockets())
				{
					// Updating the position of the ball.
					ServerUpdate update;
					update.x = football->GetPosition().x;
					update.y = football->GetPosition().y;
					update.id = football->GetID();
					update.red_score = level_generator_.GetRedTeamScore();
					update.blue_score = level_generator_.GetBlueTeamScore();
					update.time = clock_->getElapsedTime().asMilliseconds();

					// Send the server update to the client.
					network_->SendServerUpdateToClients(*socket, update);
				}

				// If the red or blue team have reached three goals.
				if (level_generator_.GetRedTeamScore() == 3 || level_generator_.GetBlueTeamScore() == 3)
				{
					// The match has now finished.
					level_generator_.SetFinished(true);
				}

				football->Update(dt);
			}
		}
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//					Data Response						//
//======================================================//
// This will provide the approriate response for the	//
// clients.												//
//////////////////////////////////////////////////////////
void Level::DataResponse(sf::TcpSocket& client_socket, sf::Packet& data, DynamicBodyRectangle& object, float dt)
{
		
	// If the data should contain input.
	if (data >> object.GetInput())
	{
		// Process input data.
		ApplyPlayerInput(object, dt);
		network_->SendInputToClients(client_socket, object.GetInput());
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//					ApplyPlayerInput					//
//======================================================//
// This will apply the commands sent to us by the		//
// clients.												//
//////////////////////////////////////////////////////////
void Level::ApplyPlayerInput(DynamicBodyRectangle& player, float dt)
{

	// If the player pressed up.
	if (player.GetInput().up)
	{
		player.GetBody()->SetAwake(true);
		player.GetBody()->ApplyLinearImpulse(b2Vec2(0.0f, kPlayerMovementForce.y * dt), player.GetBody()->GetWorldCenter(), player.GetBody()->IsAwake());
	}

	// If the player pressed right.
	if (player.GetInput().right)
	{
		player.GetBody()->SetAwake(true);
		player.GetBody()->ApplyLinearImpulse(b2Vec2((kPlayerMovementForce.x * dt), 0.0f), player.GetBody()->GetWorldCenter(), player.GetBody()->IsAwake());
	}

	// If the player pressed left.
	if (player.GetInput().left)
	{
		player.GetBody()->SetAwake(true);
		player.GetBody()->ApplyLinearImpulse(b2Vec2(((kPlayerMovementForce.x * -1.0f) * dt), 0.0f), player.GetBody()->GetWorldCenter(), player.GetBody()->IsAwake());
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
// This will check for collisions and handle object		//
// responses every frame.								//
//////////////////////////////////////////////////////////
void Level::Update(float dt)
{

	// Test for collisions and provide collision response.
	CollisionTest();

	// Handle all of our level objects.
	HandleLevelObjects(dt);

}