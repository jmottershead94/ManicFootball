// Include header file here.
#include "game_object.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Init(sf::Vector2f position, sf::Vector2f dimensions, ObjectID object_id, bool is_rectangle)
{

	// Initialising local attributes.
	position_ = position;			// Setting the position of the game object shape.
	dimension_ = dimensions;		// Setting the width and height of the game object shape.
	id_ = object_id;				// Setting the id number of the game object shape.
	on_surface_ = false;			// Letting us know if the game object is on a surfact or not.
	remove_ = false;				// Letting us know if the game object needs to be removed or not.
	is_rectangle_ = is_rectangle;	// Letting us know what kind of shape we have.
	velocity_ = { 0.0f, 0.0f };		// Setting the velocity to 0 to begin with.

}

void GameObject::InitPE(sf::Vector2f position, sf::Vector2f dimensions, ObjectID object_id, bool is_rectangle, sf::Color colour)
{

	// Initialising local attributes.
	position_ = position;			// Setting the position of the game object shape.
	dimension_ = dimensions;		// Setting the width and height of the game object shape.
	id_ = object_id;				// Setting the id number of the game object shape.
	on_surface_ = false;			// Letting us know if the game object is on a surfact or not.
	remove_ = false;				// Letting us know if the game object needs to be removed or not.
	is_rectangle_ = is_rectangle;	// Letting us know what kind of shape we have.
	velocity_ = { 0.0f, 0.0f };		// Setting the velocity to 0 to begin with.

	if (is_rectangle_)
	{
		// Setting up the rectangle shape.
		rectangle_.setPosition(GetPosition());
		rectangle_.setSize(GetDimension());
		rectangle_.setFillColor(colour);
	}
	else
	{
		// Setting up the circle shape.
		circle_.setPosition(GetPosition());
		circle_.setRadius(25.0f);
		circle_.setFillColor(colour);
	}

}

// Setters.
void GameObject::SetVelocity(float x, float y)
{
	
	velocity_.x = x;
	velocity_.y = y;

}

void GameObject::SetPositionPE(float x, float y)
{

	position_.x = x;
	position_.y = y;
	
	if (is_rectangle_)
	{
		rectangle_.setPosition(x, y);
	}
	else
	{
		circle_.setPosition(x, y);
	}

}