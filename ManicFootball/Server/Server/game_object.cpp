// Include header file here.
#include "game_object.h"

//////////////////////////////////////////////////////////
//======================================================//
//						Init							//
//======================================================//
// This will intialise the game object in a specified	//
// position, with specified dimensions, id and shape.	//
//////////////////////////////////////////////////////////
void GameObject::Init(sf::Vector2f position, sf::Vector2f dimensions, ObjectID object_id)
{

	// Initialising local attributes.
	position_ = position;			// Setting the position of the game object shape.
	respawn_position_ = position;	// Setting the intial respawn position of the object.
	dimension_ = dimensions;		// Setting the width and height of the game object shape.
	id_ = object_id;				// Setting the id number of the game object shape.

}

//////////////////////////////////////////////////////////
//======================================================//
//					TranslateBody						//
//======================================================//
// This will move the body and shape according to		//
// framework coordinates.								//
//////////////////////////////////////////////////////////
void GameObject::TranslateBody(float& x, float& y)
{

	// Set the position of the shape.
	SetPosition(sf::Vector2f(x, y));

	// Set the position of the body.
	body_->SetTransform(b2Vec2(FRAMEWORK_BOX2D_POS_X(position_.x), FRAMEWORK_BOX2D_POS_Y(position_.y)), 0.0f);

}