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

	// If we have 16 x and y coordinates.
	if ((x_positions_.size() == 16) && (y_positions_.size() == 16))
	{
		// Place in the points for the other player x position and the time they were received at.
		SetXPoints();

		// Place in the points for the other player y position and the time they were received at.
		SetYPoints();

		// This should interpolate/predict the next however many points.
		// Place in a check to make sure it doesn't stray too far.
		// If the absolute value of the x position minus the previous x position is less than the network difference in x threshold.
		if (abs(interpolation_x_(network.GetClock().getElapsedTime().asMilliseconds() + network.GetLagOffset()) - object.GetPosition().x) < (network.GetThreshold()))
		{
			// If the absolute value of the y position minus the previous y position is less than the network difference in y threshold.
			if (abs(interpolation_y_(network.GetClock().getElapsedTime().asMilliseconds() + network.GetLagOffset()) - object.GetPosition().y) < (network.GetThreshold()))
			{
				std::cout << "We are doing something." << std::endl;

				// Update the struct values.
				position_update_.x = interpolation_x_(network.GetClock().getElapsedTime().asMilliseconds());
				position_update_.y = interpolation_y_(network.GetClock().getElapsedTime().asMilliseconds());
				position_update_.time = network.GetClock().getElapsedTime().asMilliseconds() + network.GetLagOffset();

				// We can move the body through interpolation.
				object.TranslateBody(interpolation_x_(network.GetClock().getElapsedTime().asMilliseconds() + network.GetLagOffset()), interpolation_y_(network.GetClock().getElapsedTime().asMilliseconds() + network.GetLagOffset()));
				
				// Send the updated struct to the server.
				network.SendDeadReckoningMessageToServer(position_update_);
			}
		}
		//// If we are too far out with our prediction.
		//else
		//{
		//	for (int x = 0; x < x_positions_.size(); x++)
		//	{
		//		for (int y = 0; y < y_positions_.size(); y++)
		//		{
		//			object.TranslateBody(x_positions_[x], y_positions_[y]);
		//		}
		//	}
		//}

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