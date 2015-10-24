// Jason Mottershead, 1300455.

// Game object class header file.
// This class will provide the template for all of the objects in the game.

// Header guard.
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

// Include files here.
#include <Box2D\Box2D.h>
#include <SFML\System\Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "box2d_conversions.h"
#include "object_id.h"

class GameObject
{

	public:
		// Methods.
		GameObject();
		~GameObject();
		void Init(sf::Vector2f position, sf::Vector2f dimensions, ObjectID object_id);

		// Setters.
		// This function will set the current body of the game object with the body passed in.
		void SetBody(b2Body* body)	{ body_ = body; }

		// This function will set the new position of the game object.
		void SetPosition(sf::Vector2f new_position) { position_ = new_position; }

		// Getters.
		// This function will provide access to the body of the game object.
		b2Body* GetBody()			{ return body_; }

		// This function will return the rectangle shape.
		sf::RectangleShape GetRectangleShape()	{ return rectangle_; }

		// This function will return the circle shape.
		sf::CircleShape GetCircleShape() { return circle_; }

		// This function will return the current position of the game object.
		sf::Vector2f GetPosition() { return position_; }

		// This function will return the current dimension of the game object.
		sf::Vector2f GetDimension() { return dimension_; }

		// This function will return the id number of the object.
		int GetID()					{ return id_; }

		// This function will convert any radian angles into degrees.
		float RadiansToDegrees(float radians) { return (radians * (180.0f / b2_pi)); }

		// This function will convert any degree angles into radians.
		float DegreesToRadians(float degrees) { return (degrees * (b2_pi / 180.0f)); }

	protected:
		// Attributes.
		b2Body* body_;
		b2BodyDef body_def_;
		sf::RectangleShape rectangle_;
		sf::CircleShape circle_;
		sf::Vector2f position_;
		sf::Vector2f dimension_;
		ObjectID id_;

};

#endif