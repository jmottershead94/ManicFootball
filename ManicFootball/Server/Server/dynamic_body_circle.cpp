// Include header file here.
#include "dynamic_body_circle.h"

//////////////////////////////////////////////////////////
//======================================================//
//					Constructor							//
//======================================================//
//////////////////////////////////////////////////////////
DynamicBodyCircle::DynamicBodyCircle()
{
}

//////////////////////////////////////////////////////////
//======================================================//
//					Destructor							//
//======================================================//
//////////////////////////////////////////////////////////
DynamicBodyCircle::~DynamicBodyCircle()
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
void DynamicBodyCircle::Init(sf::Vector2f position, float radius, b2World* world, ObjectID object_id, const sf::Color colour)
{

	// Initialising the sprite for the body.
	GameObject::Init(position, sf::Vector2f(0.0f, 0.0f), object_id, false);

	// Setting up the circle shape.
	circle_.setRadius(radius);
	circle_.setPosition(GetPosition());
	circle_.setFillColor(colour);

	// Setting up the body definition.
	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	//body_def.position.Set(FRAMEWORK_BOX2D_POS_X(position_.x, radius), FRAMEWORK_BOX2D_POS_Y(position_.y));
	body_ = world->CreateBody(&body_def);
	body_->SetFixedRotation(false);
	body_->SetTransform(b2Vec2(FRAMEWORK_BOX2D_POS_X(position_.x), FRAMEWORK_BOX2D_POS_Y(position_.y)), 0.0f);
	
	// Creates the bounding circle for the body.
	b2CircleShape dynamic_circle;
	dynamic_circle.m_radius = (FRAMEWORK_BOX2D_SIZE(circle_.getRadius()) * BOX2D_FRAMEWORK_DYNAMIC_CIRCLE_SIZE);

	// Adds a fixture definition.
	b2FixtureDef fixture_def;
	fixture_def.shape = &dynamic_circle;	// Setting the shape of the fixture.
	fixture_def.density = 1.0f;				// Setting the density of the object.
	fixture_def.friction = 0.25f;			// How much friction the object has, how much drag it will have on a surface.
	fixture_def.restitution = 0.75f;		// How bouncy the object will be.
	body_->CreateFixture(&fixture_def);		// Applying the fixture to the body.

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
void DynamicBodyCircle::Update(float dt)
{

	// Wake up the body.
	//body_->SetAwake(true);

	// Resets the position of the shape.
	SetPosition(sf::Vector2f(BOX2D_FRAMEWORK_POS_X(body_->GetPosition().x), BOX2D_FRAMEWORK_POS_Y(body_->GetPosition().y)));

	// Moves the shape to the new position.
	circle_.setPosition(position_);

	// Sets the rotation of the sprite to the rotation of the body.
	circle_.setRotation(body_->GetAngle() * -1.0f);

}