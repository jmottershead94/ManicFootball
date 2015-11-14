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
	respawn_position_ = position;	// Setting the intial respawn position of the object.
	dimension_ = dimensions;		// Setting the width and height of the game object shape.
	id_ = object_id;				// Setting the id number of the game object shape.
	on_surface_ = false;			// Letting us know if the game object is on a surfact or not.
	remove_ = false;				// Letting us know if the game object needs to be removed or not.
	is_rectangle_ = is_rectangle;	// Letting us know what kind of shape we have.
	velocity_ = { 0.0f, 0.0f };		// Setting the velocity to 0 to begin with.

}

void GameObject::TranslateBody(float x, float y)
{

	SetPosition(sf::Vector2f(x, y));
	body_->SetTransform(b2Vec2(FRAMEWORK_BOX2D_POS_X(position_.x), FRAMEWORK_BOX2D_POS_Y(position_.y)), 0.0f);

}