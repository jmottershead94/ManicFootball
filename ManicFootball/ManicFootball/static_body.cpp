// Include header file here.
#include "static_body.h"

//////////////////////////////////////////////////////////
//======================================================//
//					Constructor							//
//======================================================//
//////////////////////////////////////////////////////////
StaticBody::StaticBody()
{
}

//////////////////////////////////////////////////////////
//======================================================//
//					Destructor							//
//======================================================//
//////////////////////////////////////////////////////////
StaticBody::~StaticBody()
{
}

//////////////////////////////////////////////////////////
//======================================================//
//						Init							//
//======================================================//
// This initialise function will set up the body		//
// definition for the static body, as well as place	the	//
// sprite in the correct location.						//
//////////////////////////////////////////////////////////
void StaticBody::Init(sf::Vector2f position, sf::Vector2f dimensions, b2World* world, ObjectID object_id, const sf::Color colour)
{

	// Initialising the id and position for the game object.
	GameObject::Init(position, dimensions, object_id);

	// Setting up the rectangle shape.
	rectangle_.setPosition(GetPosition());
	rectangle_.setSize(GetDimension());
	rectangle_.setFillColor(colour);

	// Setting up the body definition.
	b2BodyDef body_def;
	body_def.type = b2_staticBody;
	body_def.position.Set(FRAMEWORK_BOX2D_POS_X(position_.x), FRAMEWORK_BOX2D_POS_Y(position_.y));
	body_ = world->CreateBody(&body_def);
	body_->SetTransform(b2Vec2(FRAMEWORK_BOX2D_POS_X(position_.x), FRAMEWORK_BOX2D_POS_Y(position_.y)), 0.0f);

	// Creates the bounding box for the body.
	b2PolygonShape box_;
	box_.SetAsBox(FRAMEWORK_BOX2D_SIZE(dimension_.x) * BOX2D_FRAMEWORK_SIZE_OFFSET_X, FRAMEWORK_BOX2D_SIZE(dimension_.y) * BOX2D_FRAMEWORK_SIZE_OFFSET_Y);
	body_->CreateFixture(&box_, 0.0f);

	// Setting the connection between game objects and the Box2D body.
	body_->SetUserData(this);

}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
//////////////////////////////////////////////////////////
void StaticBody::Update()
{
}