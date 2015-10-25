// Include header file here.
#include "player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(sf::Vector2f position, sf::Vector2f dimensions, b2World* world)
{

	// Initialising the shape and body of the player.
	DynamicBodyRectangle::Init(position, dimensions, world, ObjectID::player, sf::Color::Blue);

	// Setting local attributes up.
	in_air_ = false;
	movement_force_.x = 2.0f;
	movement_force_.y = 10.0f;

}

void Player::Input(float dt)
{

	// If the player presses the right arrow key.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// Move the body to the right.
		body_->ApplyLinearImpulse(b2Vec2((movement_force_.x * dt), 0.0f), body_->GetWorldCenter(), body_->IsAwake());
	}
	// If the player has pressed the left arrow key.
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// Move the body to the left.
		body_->ApplyLinearImpulse(b2Vec2(((movement_force_.x * -1.0f) * dt), 0.0f), body_->GetWorldCenter(), body_->IsAwake());
	}
	
	// If the player has pressed the up arrow key.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
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