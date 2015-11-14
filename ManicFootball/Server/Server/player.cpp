// Include header file here.
#include "player.h"

Player::Player()
{
}

Player::~Player()
{
}

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

	// Initialising local attributes.
	is_red_team_ = red_team;			// Setting if the player should be on the red team or not.
	in_air_ = false;					// The player is currently not in the air.
	respawn_ = false;					// The player does not need to respawn at this moment in time.
	movement_force_.x = 2.0f;			// The movement force that will be applied in the x axis.
	movement_force_.y = 10.0f;			// The movement force that will be applied in the y axis.
	respawn_location_.x = position.x;	// The x position for respawn.
	respawn_location_.y = position.y;	// The y position for respawn.

}

void Player::Input(float dt)
{

	// If the player presses the right arrow key.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// Wake up the body.
		body_->SetAwake(true);

		// Move the body to the right.
		body_->ApplyLinearImpulse(b2Vec2((movement_force_.x * dt), 0.0f), body_->GetWorldCenter(), body_->IsAwake());
	}
	// If the player has pressed the left arrow key.
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// Wake up the body.
		body_->SetAwake(true);

		// Move the body to the left.
		body_->ApplyLinearImpulse(b2Vec2(((movement_force_.x * -1.0f) * dt), 0.0f), body_->GetWorldCenter(), body_->IsAwake());
	}
	
	// If the player has pressed the up arrow key.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// Wake up the body.
		body_->SetAwake(true);

		// Make the player jump.
		Jump(dt);
	}

}

void Player::Jump(float dt)
{

	// Checking to see if the player is already in the air.
	// If they are not currently in the air.
	if (!in_air_)
	{
		// Make the player jump upwards.
		body_->ApplyLinearImpulse(b2Vec2(0.0f, (movement_force_.y * dt)), body_->GetWorldCenter(), body_->IsAwake());

		// Set the air flag to true.
		in_air_ = true;
	}

	// Just for testing purposes.
	// The player can fly.
	in_air_ = false;

	// In level check collisions have this.
	// If the player has a surface beneath them.
	//else if (((game_object_->id_ == player) && (game_object2_->id_ == platform))
	//	|| ((game_object_->id_ == player) && (game_object2_->id_ == box)))
	//{
	//	// Allow them to jump in the air.
	//	player_.in_air_ = false;
	//}

}

void Player::Respawn()
{

	// This will set the rectangle of the player to the respawn location. 
	rectangle_.setPosition(respawn_location_);

	// This will set the body of the player to the respawn location, and to the current angle of the player.
	body_->SetTransform(b2Vec2(FRAMEWORK_BOX2D_POS_X(respawn_location_.x), FRAMEWORK_BOX2D_POS_Y(respawn_location_.y)), 0.0f);

}

void Player::Update(float dt)
{

	Input(dt);
	DynamicBodyRectangle::Update(dt);

}