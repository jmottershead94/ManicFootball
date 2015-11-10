// Include header file here.
#include "player_test.h"

PlayerTest::PlayerTest()
{
}

PlayerTest::~PlayerTest()
{
}

void PlayerTest::Init(sf::Vector2f position, sf::Vector2f dimensions, bool red_team, PhysicsEngine& physics)
{

	// If the player is on the red team.
	if (red_team)
	{
		// Initialise the shape of the player to be red.
		InitPE(position, dimensions, ObjectID::player, true, sf::Color::Red);
	}
	// Otherwise, the player is on the blue team.
	else
	{
		// Make the player blue.
		InitPE(position, dimensions, ObjectID::player, true, sf::Color::Blue);
	}

	// Initialising local attributes.
	is_red_team_ = red_team;			// Setting if the player should be on the red team or not.
	in_air_ = false;					// The player is currently not in the air.
	respawn_ = false;					// The player does not need to respawn at this moment in time.
	movement_force_.x = 2.0f;			// The movement force that will be applied in the x axis.
	movement_force_.y = 10.0f;			// The movement force that will be applied in the y axis.
	respawn_location_.x = position.x;	// The x position for respawn.
	respawn_location_.y = position.y;	// The y position for respawn.
	physics_ = &physics;

}

void PlayerTest::Input(float dt)
{

	// If the player presses the right arrow key.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && GetVelocity().x < physics_->terminal_velocity_)
	{
		physics_->ApplyAccelerationForward(*this);
	}
	// If the player has pressed the left arrow key.
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		physics_->ApplyAccelerationBackward(*this);
	}
	else
	{
		if (GetVelocity().x < 0.0f)
		{
			physics_->ApplyRetardationForward(*this);
		}
		else if (GetVelocity().x > 0.0f)
		{
			physics_->ApplyRetardationBackward(*this);
		}
		else
		{
			SetVelocity(0.0f, GetVelocity().y);
		}
	}

	// If the player has pressed the up arrow key.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// Make the player jump.
		Jump(dt);
	}

}

void PlayerTest::Jump(float dt)
{

	// Checking to see if the player is already in the air.
	// If the player is on a surface.
	if (IsOnSurface())
	{
		float time_in_air = 20.0f;

		// Make the player jump upwards.
		SetVelocity(GetVelocity().x, (GetVelocity().y - (physics_->acceleration_ * time_in_air)));

		// The player is no longer on a surface.
		OnSurface(false);
	}

	// Just for testing purposes.
	// The player can fly.
	//in_air_ = false;

	// In level check collisions have this.
	// If the player has a surface beneath them.
	//else if (((game_object_->id_ == player) && (game_object2_->id_ == platform))
	//	|| ((game_object_->id_ == player) && (game_object2_->id_ == box)))
	//{
	//	// Allow them to jump in the air.
	//	player_.in_air_ = false;
	//}

}

void PlayerTest::Respawn()
{

	// This will set the rectangle of the player to the respawn location. 
	rectangle_.setPosition(respawn_location_);

}

void PlayerTest::Update(float dt)
{

	Input(dt);
	physics_->Update(*this, dt);

}