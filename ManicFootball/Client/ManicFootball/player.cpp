// Include header file here.
#include "player.h"

//////////////////////////////////////////////////////////
//======================================================//
//						Init							//
//======================================================//
// This will intialise the player on either the red		//
// team or the blue team.								//
//////////////////////////////////////////////////////////
void Player::Init(sf::Vector2f position, sf::Vector2f dimensions, b2World* world, bool red_team)
{

	// If the player is on the red team.
	if (red_team)
	{
		// Initialise the shape of the player to be red.
		DynamicBodyRectangle::Init(position, dimensions, world, ObjectID::player, sf::Color::Red, 0.2f);
	}
	// Otherwise, the player is on the blue team.
	else
	{
		// Make the player blue.
		DynamicBodyRectangle::Init(position, dimensions, world, ObjectID::player, sf::Color::Blue, 0.2f);
	}

	// Initialsing local attributes.
	is_red_team_ = red_team;		// Is the player on the red team or not.

}

//////////////////////////////////////////////////////////
//======================================================//
//						Controls						//
//======================================================//
// Depending on which team the player is on, the		//
// controls will be different.							//
// This will also apply input for the player.			//
//////////////////////////////////////////////////////////
void Player::Controls(float dt)
{

	// If the player is on the red team.
	// Set up the controls for the red team player.
	if (is_red_team_)
	{
		// If the player presses the right arrow key.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			// The player is moving right.
			input_.right = true;
			input_.left = false;

			// Wake up the body.
			body_->SetAwake(true);

			// Move the body to the right.
			body_->ApplyLinearImpulse(b2Vec2((GetMovementForce().x * dt), 0.0f), body_->GetWorldCenter(), body_->IsAwake());
		}
		// If the player has pressed the left arrow key.
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			// The player is moving left.
			input_.right = false;
			input_.left = true;

			// Wake up the body.
			body_->SetAwake(true);

			// Move the body to the left.
			body_->ApplyLinearImpulse(b2Vec2(((GetMovementForce().x * -1.0f) * dt), 0.0f), body_->GetWorldCenter(), body_->IsAwake());
		}
		// Otherwise, if the player is not pressing anything.
		else
		{
			// The player is not moving.
			input_.right = false;
			input_.left = false;
		}

		// If the player has pressed the up arrow key.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			// The player is moving upwards.
			input_.up = true;

			// Wake up the body.
			body_->SetAwake(true);

			// Make the player jump upwards.
			body_->ApplyLinearImpulse(b2Vec2(0.0f, (GetMovementForce().y * dt)), body_->GetWorldCenter(), body_->IsAwake());
		}
		else
		{
			// The player is not moving upwards.
			input_.up = false;
		}
	}
	// Otherwise, if the player is on the blue team.
	// Set up the controls for the blue team player.
	else if (!is_red_team_)
	{
		// If the player presses the right arrow key.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			// The player is moving right.
			input_.right = true;
			input_.left = false;

			// Wake up the body.
			body_->SetAwake(true);

			// Move the body to the right.
			body_->ApplyLinearImpulse(b2Vec2((GetMovementForce().x * dt), 0.0f), body_->GetWorldCenter(), body_->IsAwake());
		}
		// If the player has pressed the left arrow key.
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// The player is moving left.
			input_.right = false;
			input_.left = true;

			// Wake up the body.
			body_->SetAwake(true);

			// Move the body to the left.
			body_->ApplyLinearImpulse(b2Vec2(((GetMovementForce().x * -1.0f) * dt), 0.0f), body_->GetWorldCenter(), body_->IsAwake());
		}
		// Otherwise, if the player is not pressing anything.
		else
		{
			// The player is not moving.
			input_.right = false;
			input_.left = false;
		}

		// If the player has pressed the up arrow key.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			// The player is moving upwards.
			input_.up = true;

			// Wake up the body.
			body_->SetAwake(true);

			// Make the player jump upwards.
			body_->ApplyLinearImpulse(b2Vec2(0.0f, (GetMovementForce().y * dt)), body_->GetWorldCenter(), body_->IsAwake());
		}
		else
		{
			// The player is not moving upwards.
			input_.up = false;
		}
	}

}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
// This will update player input and position every		//
// frame.												//
//////////////////////////////////////////////////////////
void Player::Update(float dt)
{

	// Apply player controls.
	Controls(dt);

	// Update the body of the player.
	DynamicBodyRectangle::Update(dt);

}