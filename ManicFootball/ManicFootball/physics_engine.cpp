// Include header file here.
#include "physics_engine.h"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}

bool PhysicsEngine::BoundingObjectCollider(GameObject& object_a, GameObject& object_b)
{

	// If object_a is a rectangle and object_b is a rectangle.
	if (object_a.IsRectangle() && object_b.IsRectangle())
	{
		// If the rectangle from object_a intersects/collides with the rectangle from object_b.
		if (object_a.GetRectangleShape().getGlobalBounds().intersects(object_b.GetRectangleShape().getGlobalBounds()))
		{
			// A collision has occured between the two boxes.
			return true;
		}
	}
	// If object_a is a rectangle and object_b is a circle.
	else if (object_a.IsRectangle() && !object_b.IsRectangle())
	{
		// If the rectangle from object_a intersects/collides with the rectangle from object_b.
		if (object_a.GetRectangleShape().getGlobalBounds().intersects(object_b.GetCircleShape().getGlobalBounds()))
		{
			// A collision has occured between the a box and a circle.
			return true;
		}
	}
	// If object_a is a circle and object_b is a rectangle.
	else if (!object_a.IsRectangle() && object_b.IsRectangle())
	{
		// If the rectangle from object_a intersects/collides with the rectangle from object_b.
		if (object_a.GetCircleShape().getGlobalBounds().intersects(object_b.GetRectangleShape().getGlobalBounds()))
		{
			// A collision has occured between the a circle and a box.
			return true;
		}
	}

	// Otherwise, a collision has not occured from any of the objects.
	return false;

}

// This will handle any standard collisions between DYNAMIC objects.
void PhysicsEngine::ObjectColliderResponse(GameObject& object_a, GameObject& object_b)
{

	// If object_a is already on a surface.
	if (object_a.IsOnSurface())
	{
		// Make object_a bounce off of the other object only in the x axis.
		object_a.SetVelocity((object_a.GetVelocity().x * -1.0f), 0.0f);
	}
	// Otherwise, object_a is not on a surface.
	else
	{
		// Make object_a bounce off of the other object in both x and y axis.
		object_a.SetVelocity((object_a.GetVelocity().x * -1.0f), (object_a.GetVelocity().y * -1.0f));
	}

	// If object_b is already on a surface.
	if (object_b.IsOnSurface())
	{
		// Make object_b bounce off of the other object only in the x axis.
		object_b.SetVelocity((object_b.GetVelocity().x * -1.0f), 0.0f);
	}
	// Otherwise, object_b is not on a surface.
	else
	{
		// Make object_b bounce off of the other object in both x and y axis.
		object_b.SetVelocity((object_b.GetVelocity().x * -1.0f), (object_b.GetVelocity().y * -1.0f));
	}

}

