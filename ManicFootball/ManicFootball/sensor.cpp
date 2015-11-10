// Include header file here.
#include "sensor.h"

//////////////////////////////////////////////////////////
//======================================================//
//					Constructor							//
//======================================================//
//////////////////////////////////////////////////////////
Sensor::Sensor()
{
}

//////////////////////////////////////////////////////////
//======================================================//
//					Destructor							//
//======================================================//
//////////////////////////////////////////////////////////
Sensor::~Sensor()
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
void Sensor::Init(sf::Vector2f position, sf::Vector2f dimensions, b2World* world, ObjectID object_id)
{

	// Initialising the id and position for the game object.
	GameObject::Init(position, dimensions, object_id, true);

	// Setting up the rectangle shape.
	rectangle_.setPosition(GetPosition());
	rectangle_.setSize(GetDimension());
	rectangle_.setFillColor(sf::Color::Transparent);

	// Setting up the body definition.
	b2BodyDef body_def;
	body_def.type = b2_staticBody;
	body_def.position.Set(FRAMEWORK_BOX2D_POS_X(position_.x), FRAMEWORK_BOX2D_POS_Y(position_.y));
	body_ = world->CreateBody(&body_def);
	body_->SetTransform(b2Vec2(FRAMEWORK_BOX2D_POS_X(position_.x), FRAMEWORK_BOX2D_POS_Y(position_.y)), 0.0f);

	// Creates the bounding box for the body.
	b2PolygonShape box_;
	b2FixtureDef fixture_def;
	box_.SetAsBox(FRAMEWORK_BOX2D_SIZE(dimension_.x) * BOX2D_FRAMEWORK_STATIC_RECTANGLE_SIZE_X, FRAMEWORK_BOX2D_SIZE(dimension_.y) * BOX2D_FRAMEWORK_STATIC_RECTANGLE_SIZE_Y);
	fixture_def.shape = &box_;
	fixture_def.isSensor = true;
	fixture_def.filter.categoryBits = Category::net;
	fixture_def.filter.maskBits = Category::ball;		// The sensor should only collide with the ball.
	body_->CreateFixture(&fixture_def);
	

	// Setting the connection between game objects and the Box2D body.
	body_->SetUserData(this);

}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
//////////////////////////////////////////////////////////
void Sensor::Update()
{
}