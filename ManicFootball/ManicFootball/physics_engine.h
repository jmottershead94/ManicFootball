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
		const float gravity_ = 1.0f;			// How much gravity will be applied every frame.
		const float acceleration_ = 1.0f;		// How much acceleration will be applied to objects.
		const float retardation_ = 1.0f;		// How much deceleration will be applied to objects.
		const float terminal_velocity_ = 4.0f;

		// Methods.
		PhysicsEngine();
		~PhysicsEngine();
		void Init();
		bool BoundingObjectCollider(GameObject& object_a, GameObject& object_b, float dt);
		bool BoundingBoxCollider(GameObject& object_a, GameObject& object_b);
		bool BoundingBoxCircleCollider(GameObject& object_a, GameObject& object_b);
		void ObjectColliderResponse(GameObject& object_a, GameObject& object_b, float dt);
		void SurfaceCollisionResponse(GameObject& object_a, GameObject& object_b);
		void BoxesCollisionResponse(GameObject& object_a, GameObject& object_b, float dt);
		void CircleCollisionResponse(GameObject& object_a, GameObject& object_b, float dt);
		void WallCollision(GameObject& object);
		void ApplyGravity(GameObject& object, float dt);
		void Update(GameObject& object, float dt);

		// Setters.
		// This will apply the velocity of the object; it makes it move.
		inline void ApplyVelocities(GameObject& object, float dt)		{ object.SetPositionPE((object.GetPosition().x + (object.GetVelocity().x)), (object.GetPosition().y + (object.GetVelocity().y))); }

		// This function will move an object forward.
		inline void ApplyAccelerationForward(GameObject& object)		{ object.SetVelocity((object.GetVelocity().x + acceleration_), 0.0f); };

		// This function will move the object backwards.
		inline void ApplyAccelerationBackward(GameObject& object)		{ object.SetVelocity((object.GetVelocity().x - acceleration_), 0.0f); };

		// This function will apply retardation (friction) forward - used to stop the player moving backwards.
		inline void ApplyRetardationForward(GameObject& object)			{ object.SetVelocity((object.GetVelocity().x + retardation_), 0.0f); };

		// This function will apply retardation (friction) backward - used to stop the player moving forwards.
		inline void ApplyRetardationBackward(GameObject& object)		{ object.SetVelocity((object.GetVelocity().x - retardation_), 0.0f); };

		// This function will provide the response for an object colliding with the side of the screen.
		inline void SideSurfaceCollisionResponse(GameObject& object)	{ object.SetVelocity((object.GetVelocity().x * -2.0f), 0.0f); };

		// This function will provide a response for an object colliding with a surface beneath them.
		inline void BottomSurfaceCollisionResponse(GameObject& object)	{ object.SetVelocity((object.GetVelocity().x - retardation_), 0.0f); };

};

#endif