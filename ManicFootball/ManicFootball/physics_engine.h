// Jason Mottershead, 1300455.

// Physics Engine class header file.
// This class will handle all of the basic physics for the game, and detect collisions.

// Header guard.
#ifndef _PHYSICS_ENGINE_H_
#define _PHYSICS_ENGINE_H_

// Include files here.
#include "game_object.h"

class PhysicsEngine
{

	public:
		// Attributes.
		const float gravity_ = 1.0f;		// How much gravity will be applied every frame.
		const float acceleration = 1.0f;	// How much acceleration will be applied to objects.
		const float retardation = 1.0f;		// How much deceleration will be applied to objects.

		// Methods.
		PhysicsEngine();
		~PhysicsEngine();
		void Init();
		bool BoundingObjectCollider(GameObject& object_a, GameObject& object_b);
		bool BoundingBoxCollider(GameObject& object_a, GameObject& object_b);
		bool BoundingBoxCircleCollider(GameObject& object_a, GameObject& object_b);
		void ObjectColliderResponse(GameObject& object_a, GameObject& object_b);
		void WallCollision(GameObject& object);
		void ApplyGravity(GameObject& object);
		void ApplyVelocities(GameObject& object);
		void Update(GameObject& object, bool);

		// Setters.
		// This function will move an object forward.
		inline void ApplyAccelerationForward(GameObject& object)		{ object.SetVelocity((object.GetVelocity().x + acceleration), 0.0f); };

		// This function will move the object backwards.
		inline void ApplyAccelerationBackward(GameObject& object)		{ object.SetVelocity((object.GetVelocity().x - acceleration), 0.0f); };

		// This function will apply retardation (friction) forward - used to stop the player moving backwards.
		inline void ApplyRetardationForward(GameObject& object)			{ object.SetVelocity((object.GetVelocity().x + retardation), 0.0f); };

		// This function will apply retardation (friction) backward - used to stop the player moving forwards.
		inline void ApplyRetardationBackward(GameObject& object)		{ object.SetVelocity((object.GetVelocity().x - retardation), 0.0f); };

		// This function will provide the response for an object colliding with the side of the screen.
		inline void SideSurfaceCollisionResponse(GameObject& object)	{ object.SetVelocity((object.GetVelocity().x * -2.0f), 0.0f); };

		// This function will provide a response for an object colliding with a surface beneath them.
		inline void BottomSurfaceCollisionResponse(GameObject& object)	{ object.SetVelocity((object.GetVelocity().x - retardation), 0.0f); };

};

#endif