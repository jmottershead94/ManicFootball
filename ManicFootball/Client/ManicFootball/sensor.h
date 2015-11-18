// Jason Mottershead, 1300455.

// Sensor class header file.
// This class will contain all of the information for starting a static sensor.

// Header guard.
#ifndef _SENSOR_H_
#define _SENSOR_H_

// Include files here.
#include "game_object.h"

// Static body IS A game object, therefore inherits from it.
class Sensor : public GameObject
{

	public:
		// Methods.
		Sensor();
		~Sensor();
		void Init(sf::Vector2f position, sf::Vector2f dimensions, b2World* world, ObjectID object_id);
		void Update();

};

#endif

