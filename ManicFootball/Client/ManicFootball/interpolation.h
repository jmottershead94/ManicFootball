// Jason Mottershead, 1300455.

// Interpolation class header file.
// This class will provide the means for the client to connect to a server.

// Header guard.
#ifndef _INTERPOLATION_H_
#define _INTERPOLATION_H_

// Include files here.
#include <vector>
#include <SFML\System\Clock.hpp>
#include "tk_spline.h"
#include "dynamic_body_rectangle.h"
#include "network.h"

class Interpolation
{

	public:
		// Methods.
		Interpolation();
		~Interpolation();
		void UpdateVectors(float& x, float& y, sf::Int32& time);
		void Interpolate(DynamicBodyRectangle& object, Network& network, float dt);
		void ClearVectors();
		
		// Setters.
		// This will set the x points and the times on the cubic spline graph.
		inline void Interpolation::SetXPoints() { interpolation_x_.set_points(times_, x_positions_); }

		// This will set the y points and the times on the cubic spline graph.
		inline void Interpolation::SetYPoints() { interpolation_y_.set_points(times_, y_positions_); }

		// Getters.
		// This will return whether or not we are currently interpolating player positions.
		inline bool& IsInterpolating()						{ return interpolating_; }
		
	private:
		// Attributes.
		const unsigned int kPositionSampleSize = 4;				// The amount of positions we want from the other player on the server.
		bool interpolating_;									// Whether or not we should currently be interpolating and not using player input.
		std::vector < double > x_positions_, y_positions_;		// Vectors for storing the player coordinates over time.
		std::vector < double > times_;							// The vector storing the times that the positions were sent at.
		tk::spline interpolation_x_, interpolation_y_;			// This will be used to interpolate the other player's position.
		ServerUpdate position_update_;							// The current position update message for our interpolation.

};

#endif