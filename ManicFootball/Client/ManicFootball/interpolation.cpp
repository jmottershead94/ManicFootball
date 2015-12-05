#include "interpolation.h"

Interpolation::Interpolation()
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

void Interpolation::Calculate(GameObject& object, Network& network)
{

	// If we have 4 x and y coordinates.
	if ((x_positions_.size() == 4) && (y_positions_.size() == 4))
	{
		// Place in the points for the other player x position and the time they were received at.
		SetXPoints();

		// Place in the points for the other player y position and the time they were received at.
		SetYPoints();

		// This should interpolate/predict the next however many points.
		// Place in a check to make sure it doesn't stray too far.
		// If the absolute value of the new x position minus the previous x position is less than the network difference in x threshold.
		if (abs(interpolation_x_(network.GetClock().getElapsedTime().asMilliseconds() - 500) - object.GetPosition().x) < (network.GetThreshold()))
		{
			// If the absolute value of the new y position minus the previous y position is less than the network difference in y threshold.
			if (abs(interpolation_y_(network.GetClock().getElapsedTime().asMilliseconds() - 500) - object.GetPosition().y) < (network.GetThreshold()))
			{
				std::cout << "We are doing something." << std::endl;

				// Update the struct values.
				position_update_.x = interpolation_x_(network.GetClock().getElapsedTime().asMilliseconds());
				position_update_.y = interpolation_y_(network.GetClock().getElapsedTime().asMilliseconds());
				position_update_.time = network.GetClock().getElapsedTime().asMilliseconds() /*+ network.GetLagOffset()*/;

				// We can move the body through interpolation.
				object.TranslateBody(interpolation_x_(network.GetClock().getElapsedTime().asMilliseconds() - 500), interpolation_y_(network.GetClock().getElapsedTime().asMilliseconds() - 500));
				
				// Send the updated struct to the server.
				network.SendDeadReckoningMessageToServer(position_update_);
			}
		}
		// Otherwise, we are too far out with our interpolation.
		//else
		//{
		//	// Just use the interpolated positions.
		//	object.TranslateBody(interpolation_x_(network.GetClock().getElapsedTime().asMilliseconds()), interpolation_y_(network.GetClock().getElapsedTime().asMilliseconds()));
		//}
		// If we are too far out with our prediction.
		/*else
		{
			for (int x = 0; x < x_positions_.size(); x++)
			{
				for (int y = 0; y < y_positions_.size(); y++)
				{
					object.TranslateBody(x_positions_[x], y_positions_[y]);
				}
			}
		}*/

		// Clear all of the vectors for the next set of positions.
		ClearVectors();
	}

}

//void Interpolate(deltaTime)
//{
//	difference = unit.RemoteX - unit.LocalX
//		if (difference < threshold)
//			unit.LocalX = unit.RemoteX
//		else
//		unit.LocalX += difference * deltaTime * interpolation_constant
//}

void Interpolation::CalculateTest(GameObject& object, Network& network, float dt)
{

	// And if we have "X" x and y coordinates.
	if ((x_positions_.size() == kPositionSampleSize) && (y_positions_.size() == kPositionSampleSize))
	{
		// Store the latest position from the server.
		sf::Vector2f remote_position(x_positions_[kPositionSampleSize - 1], y_positions_[kPositionSampleSize - 1]);

		// Calculate the difference in the server and client positions.
		sf::Vector2f difference(abs(remote_position.x - object.GetPosition().x), abs(remote_position.y - object.GetPosition().y));
			
		// If our calculated x position difference is within the network threshold.
		if (difference.x < network.GetThreshold())
		{
			// And if our calculated y position difference is within the network threshold.
			if (difference.y < network.GetThreshold())
			{
				// We can move the body just through interpolation.
				object.TranslateBody(remote_position.x, remote_position.y);
			}
		}
		// Otherwise, we are too far out with our positions from the server, we will use interpolation.
		else
		{
			// Place in the points for the other player x position and the time they were received at.
			SetXPoints();

			// Place in the points for the other player y position and the time they were received at.
			SetYPoints();

			// Calculating the interpolation distance for our next point.
			sf::Vector2f interpolating_distance(interpolation_x_(network.GetClock().getElapsedTime().asMilliseconds()), interpolation_y_(network.GetClock().getElapsedTime().asMilliseconds()));

			// This should move slowly towards the position we should be currently in!
			object.TranslateBody(interpolating_distance.x, interpolating_distance.y);
		}

		// Clear all of the vectors for the next set of positions.
		ClearVectors();
	}

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