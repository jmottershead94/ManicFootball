#include "dynamic_body_rectangle.h"

//////////////////////////////////////////////////////////
//======================================================//
//					Constructor							//
//======================================================//
//////////////////////////////////////////////////////////
DynamicBodyRectangle::DynamicBodyRectangle()
{
}

//////////////////////////////////////////////////////////
//======================================================//
//					Destructor							//
//======================================================//
//////////////////////////////////////////////////////////
DynamicBodyRectangle::~DynamicBodyRectangle()
{
}

//////////////////////////////////////////////////////////
//======================================================//
//						Init							//
//======================================================//
// This initialise function will set up the body		//
// definition for the dynamic body, as well as place	//
// the sprite in the correct location.					//
//////////////////////////////////////////////////////////
void DynamicBodyRectangle::Init(sf::Vector2f position, sf::Vector2f dimensions, b2World* world, ObjectID object_id)
{

	// Initialising the sprite for the body.
	GameObject::Init(position, dimensions, object_id);

	rectangle_.setPosition(GetPosition());
	rectangle_.setSize(GetDimension());
	rectangle_.setFillColor(sf::Color::White);

	// Setting up the body definition.
	body_def_.type = b2_dynamicBody;
	body_def_.position.Set(FRAMEWORK_BOX2D_POS_X(position_.x), FRAMEWORK_BOX2D_POS_Y(position_.y));
	body_ = world->CreateBody(&body_def_);
	body_->SetFixedRotation(true);
	body_->SetTransform(b2Vec2(FRAMEWORK_BOX2D_POS_X(position_.x), FRAMEWORK_BOX2D_POS_Y(position_.y)), 0.0f);

	// Creates the bounding box for the body.
	b2PolygonShape dynamic_box;
	dynamic_box.SetAsBox(FRAMEWORK_BOX2D_SIZE(dimension_.x) * 0.7f, FRAMEWORK_BOX2D_SIZE(dimension_.y) * 0.7f);

	// Adds a fixture definition.
	b2FixtureDef fixture_def;
	fixture_def.shape = &dynamic_box;
	fixture_def.density = 1.0f;
	fixture_def.friction = 0.1f;
	fixture_def.restitution = 0.2f;
	body_->CreateFixture(&fixture_def);

	// Setting the connection between game objects and the Box2D body.
	body_->SetUserData(this);

}

//////////////////////////////////////////////////////////
//======================================================//
//						Update							//
//======================================================//
// The body will fall due to gravity, therefore this 	//
// function will set the x and y position of the sprite	//
// and the body correctly every frame.					//
//////////////////////////////////////////////////////////
void DynamicBodyRectangle::Update(float dt)
{

	// Resets the position of the shape.
	SetPosition(sf::Vector2f(BOX2D_FRAMEWORK_POS_X(body_->GetPosition().x), BOX2D_FRAMEWORK_POS_Y(body_->GetPosition().y)));
	
	// Moves the shape to the new position.
	rectangle_.setPosition(position_);

}