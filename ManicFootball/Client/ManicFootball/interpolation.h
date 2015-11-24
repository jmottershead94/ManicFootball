#ifndef _INTERPOLATION_H_
#define _INTERPOLATION_H_

#include <vector>
#include <SFML\System\Clock.hpp>
#include "tk_spline.h"
#include "game_object.h"
#include "network.h"

class Interpolation
{

	public:
		// Methods.
		Interpolation();
		~Interpolation();
		void UpdateVectors(float& x, float& y, sf::Int32& time);
		void Calculate(GameObject& object, Network& network);
		void ClearVectors();

		// Setters.
		// This will set the x points and the times on the cubic spline graph.
		inline void Interpolation::SetXPoints() { interpolation_x_.set_points(times_, x_positions_); }

		// This will set the y points and the times on the cubic spline graph.
		inline void Interpolation::SetYPoints() { interpolation_y_.set_points(times_, y_positions_); }

		// Getters.
		// This will return all of the current x positions stored.
		inline std::vector<double>& GetXPositions()			{ return x_positions_; }

		// This will return all of the current y positions stored.
		inline std::vector<double>& GetYPositions()			{ return y_positions_; }

		// This will return all of the times stored.
		inline std::vector<double>& GetTimes()				{ return times_; }

		// This will return the cubic spline for x positions.
		inline tk::spline& GetInterpolationX()				{ return interpolation_x_; }

		// This will return the cubic spline for y positions.
		inline tk::spline& GetInterpolationY()				{ return interpolation_y_; }

		// This will return the position update message for interpolation.
		inline PositionUpdate& GetPositionUpdateMessage()	{ return position_update_; }

	private:
		// Attributes.
		std::vector < double > x_positions_, y_positions_;		// Vectors for storing the player coordinates over time.
		std::vector < double > times_;							// The vector storing the times that the positions were sent at.
		tk::spline interpolation_x_, interpolation_y_;			// This will be used to interpolate the other player's position.
		PositionUpdate position_update_;

};

#endif