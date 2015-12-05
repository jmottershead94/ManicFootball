#include "interpolation.h"

Interpolation::Interpolation() : interpolating_(false)
{
}

Interpolation::~Interpolation()
{
}

void Interpolation::UpdateVectors(float& x, float& y, sf::Int32& time)
{

	// Placing all of the values into their corresponding vectors.
	x_positions_.push_back(x);
	y_positions_.push_back(y);
	times_.push_back(time);

}

//void Interpolate(deltaTime)
//{
//	difference = unit.RemoteX - unit.LocalX
//		if (difference < threshold)
//			unit.LocalX = unit.RemoteX
//		else
//		unit.LocalX += difference * deltaTime * interpolation_constant
//}

void Interpolation::Interpolate(DynamicBodyRectangle& object, Network& network, float dt)
{

	// And if we have "X" x and y coordinates.
	if ((x_positions_.size() == kPositionSampleSize) && (y_positions_.size() == kPositionSampleSize))
	{
		// Store the first position from the server.
		sf::Vector2f remote_position(x_positions_[kPositionSampleSize - 1], y_positions_[kPositionSampleSize - 1]);

		// Calculate the difference in the server and client positions.
		sf::Vector2f position_difference(abs(remote_position.x - object.GetPosition().x), abs(remote_position.y - object.GetPosition().y));
		
		// Calculate the difference in time from when we received the last network message.
		//sf::Int32 time_difference = times_[kPositionSampleSize - 1] - network.GetClock().getElapsedTime().asMilliseconds();
		
		// If our calculated position difference is within the network threshold.
		if ((position_difference.x < network.GetThreshold()) && (position_difference.y < network.GetThreshold()))
		{
			// We are not interpolating positions.
			interpolating_ = false;

			std::cout << "Using the remote position." << std::endl;

			// We can move the body just through interpolation.
			object.TranslateBody(remote_position.x, remote_position.y);
		}
		// Otherwise, we are too far out with our positions from the server, we will use interpolation.
		else
		{
			// We are interpolating positions.
			interpolating_ = true;

			std::cout << "We are too far out of the threshold." << std::endl;
			
			// Place in the points for the other player x position and the time they were received at.
			SetXPoints();

			// Place in the points for the other player y position and the time they were received at.
			SetYPoints();

			sf::Vector2f interpolating_distance;

			// For each time stamp we have received from the server with these positions.
			for (auto& time : times_)
			{
				// Calculating the interpolation distance for our next position (which was in the past!).
				interpolating_distance.x = interpolation_x_(time);
				interpolating_distance.y = interpolation_y_(time);

				// TESTING.
				std::cout << "Interpolation Distance X = " << interpolating_distance.x << " Y = " << interpolating_distance.y << std::endl;

				// This should move slowly towards the position we should be currently in!
				object.TranslateBody(interpolating_distance.x, interpolating_distance.y);
			}
		}

		// Clear all of the vectors for the next set of positions.
		ClearVectors();
	}

	// We are not interpolating positions anymore.
	interpolating_ = false;

}

void Interpolation::ClearVectors()
{

	// If there are values in the vector.
	if (!x_positions_.empty())
	{
		// Clear out the vector.
		x_positions_.clear();
	}

	if (!y_positions_.empty())
	{
		y_positions_.clear();
	}

	if (!times_.empty())
	{
		times_.clear();
	}

}