// Including the header file here.
#include "vector2.h"

// This is used for creating the vector.
Vector2::Vector2(float x, float y)
{

	// Sets each element in the vector.
	this->elements_[0] = x;
	this->elements_[1] = y;

}

// Cleaning up any variables here.
Vector2::~Vector2()
{
}

// Copying the current vector2 for use in another vector2 object.
Vector2 Vector2::copy()
{

	Vector2 copy
	(
		this->elements_[0],
		this->elements_[1]
	);

	return copy;

}

// Makes the vector2 equal to another vector2.
bool Vector2::equals(const Vector2& v2, float epsilon)
{

	return ((std::abs(this->elements_[0] - v2[0]) < epsilon) &&
		(std::abs(this->elements_[1] - v2[1]) < epsilon));

}

// Returns the length of the vector2 object.
float Vector2::length()
{

	return std::sqrt(this->lengthSquared());

}

// Returns the length of the vector2 object squared.
float Vector2::lengthSquared()
{

	return 
	(
		this->elements_[0] * this->elements_[0] +
		this->elements_[1] * this->elements_[1]
	);

}

// Returns the vector2 normalized.
Vector2& Vector2::normalize()
{

	float mag = this->length();

	if (mag)
	{
		float multiplier = 1.0f / mag;
		this->elements_[0] *= multiplier;
		this->elements_[1] *= multiplier;
	}

	return *this;

}

// Calculates the cross product of the vector2 object with another vector2.
Vector2 Vector2::cross(const Vector2& v2)
{

	Vector2 cross
	(
		(this->elements_[0] * v2[1] - this->elements_[1] * v2[0])
	);

	return cross;

}

// Subtracts one vector2 from another vector2.
Vector2 Vector2::subtract(const Vector2& v1, float scale)
{

	Vector2 sub
	(
		(this->elements_[0] - v1[0] * scale),
		(this->elements_[1] - v1[1] * scale)
	);

	return sub;

}

// Sets the values of the vector2 elements.
Vector2& Vector2::set(float x, float y)
{

	this->elements_[0] = x;
	this->elements_[1] = y;

	return *this;

}

// Sets only the x value of the vector2.
Vector2& Vector2::setX(float x)
{

	this->elements_[0] = x;
	return *this;

}

// Sets only the y value of the vector2.
Vector2& Vector2::setY(float y)
{

	this->elements_[1] = y;
	return *this;

}

// Returns the x value of the vector2.
float Vector2::getX()
{

	return this->elements_[0];

}

// Returns the y value of the vector2.
float Vector2::getY()
{

	return this->elements_[1];

}

// Returns the dot product of the vector2 object against another vector2.
float Vector2::dot(const Vector2& v2)
{

	return 
	(
		this->elements_[0] * v2[0] +
		this->elements_[1] * v2[1]
	);

}

// Scales the vector2 object.
Vector2 Vector2::scale(float scale)
{

	Vector2 scaled
	(
		(this->elements_[0] * scale),
		(this->elements_[1] * scale)
	);

	return scaled;

}

// Adds a vector2 with another vector2.
Vector2 Vector2::add(const Vector2& v1, float scale)
{

	Vector2 sum
	(
		(this->elements_[0] + v1[0] * scale),
		(this->elements_[1] + v1[1] * scale)
	);

	return sum;

}

// Performs the [] operator on the vector2 to return the position of the element.
float Vector2::operator[](int pos) const
{

	return elements_[pos];

}

// Performs the + operators to add to the vector2.
Vector2 Vector2::operator+(const Vector2& v2) 
{

	return this->add(v2);

}

// Performs the - operator to subtract from the vector2.
Vector2 Vector2::operator-(const Vector2& v2)
{

	return this->subtract(v2);

}

// Adds a vector2 onto itself with another vector2.
Vector2& Vector2::operator+=(const Vector2& v2)
{

	this->elements_[0] += v2[0];
	this->elements_[1] += v2[1];

	return *this;

}

// Subtracts a vector2 onto itself with another vector2.
Vector2& Vector2::operator-=(const Vector2& v2)
{

	this->elements_[0] -= v2[0];
	this->elements_[1] -= v2[1];

	return *this;

}

// Multiples the elements in the vector2.
Vector2& Vector2::operator*=(const float f)
{

	this->elements_[0] *= f;
	this->elements_[1] *= f;

	return *this;

}