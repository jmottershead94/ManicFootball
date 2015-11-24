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