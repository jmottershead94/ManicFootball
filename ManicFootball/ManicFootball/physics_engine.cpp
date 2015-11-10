// Include header file here.
#include "physics_engine.h"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}

bool PhysicsEngine::BoundingObjectCollider(GameObject& object_a, GameObject& object_b, float dt)
{

	// If object_a is a rectangle and object_b is a rectangle.
	if (object_a.IsRectangle() && object_b.IsRectangle())
	{
		// If the rectangle from object_a intersects/collides with the rectangle from object_b.
		if (object_a.GetRectangleShape().getGlobalBounds().intersects(object_b.GetRectangleShape().getGlobalBounds()))
		{
			// Provides standard collision responses.
			ObjectColliderResponse(object_a, object_b, dt);

			// A collision has occured between the two boxes.
			return true;
		}
	}

	// If object_a is a rectangle and object_b is a circle.
	if (object_a.IsRectangle() && !object_b.IsRectangle())
	{
		// If the rectangle from object_a intersects/collides with the circle from object_b.
		if (object_a.GetRectangleShape().getGlobalBounds().intersects(object_b.GetCircleShape().getGlobalBounds()))
		{
			// Provides standard collision responses.
			ObjectColliderResponse(object_a, object_b, dt);

			// A collision has occured between the a box and a circle.
			return true;
		}
	}

	// If object_a is a circle and object_b is a rectangle.
	if (!object_a.IsRectangle() && object_b.IsRectangle())
	{
		// If the circle from object_a intersects/collides with the rectangle from object_b.
		if (object_a.GetCircleShape().getGlobalBounds().intersects(object_b.GetRectangleShape().getGlobalBounds()))
		{
			// Provides standard collision responses.
			ObjectColliderResponse(object_a, object_b, dt);

			// A collision has occured between the a circle and a box.
			return true;
		}
	}

	// Otherwise, a collision has not occured from any of the objects.
	return false;

}

// This will handle any standard collisions for DYNAMIC objects.
void PhysicsEngine::ObjectColliderResponse(GameObject& object_a, GameObject& object_b, float dt)
{
	
	// Handling all standard surface collision responses.
	// This is what happens when the dynamic boxes interact with surfaces.
	SurfaceCollisionResponse(object_a, object_b);

	// Handling all standard dynamic boxes collision response, based on current surface state.
	// Two boxes colliding.
	BoxesCollisionResponse(object_a, object_b, dt);
	
	// Handling all dynamic circle collision responses, the circles shouldn't care about any other objects.
	// They should just bounce whatever they touch.
	CircleCollisionResponse(object_a, object_b, dt);

}

void PhysicsEngine::SurfaceCollisionResponse(GameObject& object_a, GameObject& object_b)
{

	// Standard platform collision responses.
	// If object_a is a rectangle and the colliding object is a surface.
	if (object_a.IsRectangle() && object_b.GetID() == ObjectID::surface)
	{
		// object_a is now on a surface.
		object_a.OnSurface(true);
	}
	// Otherwise, if object_a is a rectangle and is colliding with anything other than a surface.
	else if (object_a.IsRectangle() && object_b.GetID() != ObjectID::surface)
	{
		// object_a is no longer on a surface.
		object_a.OnSurface(false);
	}

	// If object_a is a surface, and the colliding object is a rectangle.
	if (object_a.GetID() == ObjectID::surface && object_b.IsRectangle())
	{
		// object_b is now on a surface.
		object_b.OnSurface(true);
	}
	// Otherwise, if object_a is anything other than a surface and is colliding with object_b.
	else if (object_a.GetID() != ObjectID::surface && object_b.IsRectangle())
	{
		// object_b is no longer on a surface.
		object_b.OnSurface(false);
	}

}

void PhysicsEngine::BoxesCollisionResponse(GameObject& object_a, GameObject& object_b, float dt)
{

	// Standard dynamic objects collision responses.
	// If object_a is already on a surface.
	if (object_a.IsOnSurface())
	{
		// Make object_a bounce off of the other object only in the x axis.
		object_a.SetVelocity(((object_a.GetVelocity().x * -1.0f) * dt), 0.0f);
	}
	// Otherwise, object_a is not on a surface.
	else
	{
		// Make object_a bounce off of the other object in both x and y axis.
		object_a.SetVelocity(((object_a.GetVelocity().x * -1.0f) * dt), ((object_a.GetVelocity().y * -1.0f) * dt));
	}

	// If object_b is already on a surface.
	if (object_b.IsOnSurface())
	{
		// Make object_b bounce off of the other object only in the x axis.
		object_b.SetVelocity(((object_b.GetVelocity().x * -1.0f) * dt), 0.0f);
	}
	// Otherwise, object_b is not on a surface.
	else
	{
		// Make object_b bounce off of the other object in both x and y axis.
		object_b.SetVelocity(((object_b.GetVelocity().x * -1.0f) * dt), ((object_b.GetVelocity().y * -1.0f) * dt));
	}

}

void PhysicsEngine::CircleCollisionResponse(GameObject& object_a, GameObject& object_b, float dt)
{

	// Standard dynamic objects collision responses.
	// If object_a is a circle.
	if (!object_a.IsRectangle())
	{
		object_a.OnSurface(false);

		// Bounce the circle off of any of the other objects.
		object_a.SetVelocity(((object_a.GetVelocity().x * -1.0f) * dt), ((object_a.GetVelocity().y * -1.0f) * dt));
	}

	// If object_b is a circle.
	if (!object_b.IsRectangle())
	{
		object_b.OnSurface(false);

		// Bounce the circle off of any of the other objects.
		object_b.SetVelocity(((object_b.GetVelocity().x * -1.0f) * dt), ((object_b.GetVelocity().y * -1.0f) * dt));
	}
}

// Applying gravity.
void PhysicsEngine::ApplyGravity(GameObject& object, float dt)
{
	
	// If the object is not on a surface.
	if (!object.IsOnSurface())
	{
		// Apply gravity to the object.
		object.SetVelocity((object.GetVelocity().x), ((object.GetVelocity().y + gravity_)));
	}

}

void PhysicsEngine::Update(GameObject& object, float dt)
{

	ApplyGravity(object, dt);
	ApplyVelocities(object, dt);
	
	// Do this check in level?
	// Handling collisions.
	//BoundingObjectCollider(object_a, object_b, dt);

}