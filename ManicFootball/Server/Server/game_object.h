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
		void Init(sf::Vector2f position, sf::Vector2f dimensions, ObjectID object_id);
		void TranslateBody(float& x, float& y);

		// Setters.
		// This function will set the new position of the game object.
		inline void SetPosition(sf::Vector2f new_position)	{ position_ = new_position; }
		
		// Getters.
		// This function will provide access to the body of the game object.
		inline b2Body* GetBody()						{ return body_; }

		// This function will return the rectangle shape.
		inline sf::RectangleShape& GetRectangleShape()	{ return rectangle_; }
		
		// This function will return the current position of the game object.
		inline sf::Vector2f& GetPosition()				{ return position_; }
			
		// This function will return the current respawn position of the game object.
		inline sf::Vector2f& GetRespawnPosition()		{ return respawn_position_; }

		// This function will return the current dimension of the game object.
		inline sf::Vector2f& GetDimension()				{ return dimension_; }

		// This function will return the id number of the object.
		inline int GetID()								{ return id_; }
		
	protected:
		// Attributes.
		b2Body* body_;
		sf::RectangleShape rectangle_;
		sf::Vector2f position_;
		sf::Vector2f respawn_position_;
		sf::Vector2f dimension_;
		ObjectID id_;

};

#endif