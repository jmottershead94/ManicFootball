// Include header file here.
#include "game_object.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Init(sf::Vector2f position, sf::Vector2f dimensions, ObjectID object_id)
{

	// Setting local game object variables.
	position_ = position;		// Setting the position of the game object shape.
	dimension_ = dimensions;	// Setting the width and height of the game object shape.
	id_ = object_id;			// Setting the id number of the game object shape.

}