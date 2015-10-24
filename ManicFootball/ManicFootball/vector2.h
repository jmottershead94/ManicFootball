// Jason Mottershead, Student Number 1300455.

// Vector2 class header file.
// This will be used for storing two-dimensional coordinates.

// Header guard.
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

// Include files here.
#include <cmath>
#include <iostream>

// A class for storing 2D coordinates.
class Vector2
{

	public:
		// Methods.
		Vector2(float x = 0, float y = 0);
		~Vector2();
		Vector2 copy();

		Vector2& set(float x, float y);
		Vector2& setX(float x);
		Vector2& setY(float y);

		float getX();
		float getY();

		Vector2 add(const Vector2& v1, float scale = 1.0);
		Vector2 subtract(const Vector2& v1, float scale = 1.0);
		Vector2 scale(float scale);

		float dot(const Vector2& v2);
		Vector2 cross(const Vector2& v2);

		Vector2& normalize();
		float length();
		float lengthSquared();

		bool equals(const Vector2& v2, float epsilon);
		float operator[](int pos) const;

		Vector2 operator+(const Vector2& v2);
		Vector2 operator-(const Vector2& v2);

		Vector2& operator+=(const Vector2& v2);
		Vector2& operator-=(const Vector2& v2);
		Vector2& operator*=(const float f);

	private:
		// Attributes.
		float elements_[2];

};

#endif