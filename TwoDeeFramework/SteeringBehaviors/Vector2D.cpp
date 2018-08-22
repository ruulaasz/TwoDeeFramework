#include "Vector2D.h"
#include <cmath>

namespace SB
{
	Vector2D::Vector2D(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Vector2D::~Vector2D()
	{

	}

	void Vector2D::operator+=(const Vector2D & _vector)
	{
		x += _vector.x;
		y += _vector.y;
	}

	void Vector2D::operator*=(const Vector2D & _vector)
	{
		x *= _vector.x;
		y *= _vector.y;
	}

	Vector2D Vector2D::operator-(const Vector2D & _vector)
	{
		Vector2D result;

		result.x = x - _vector.x;
		result.y = y - _vector.y;

		return result;
	}

	Vector2D Vector2D::operator+(const Vector2D & _vector)
	{
		Vector2D result;

		result.x = x + _vector.x;
		result.y = y + _vector.y;

		return result;
	}

	Vector2D Vector2D::operator*(const Vector2D & _vector)
	{
		Vector2D result;

		result.x = x * _vector.x;
		result.y = y * _vector.y;

		return result;
	}

	Vector2D Vector2D::operator*(const float & _value)
	{
		return Vector2D(x * _value, y * _value);
	}

	Vector2D Vector2D::operator/(const float & _value)
	{
		return Vector2D(x / _value, y / _value);
	}

	float getLength(Vector2D _vector)
	{
		return std::sqrt(std::pow(_vector.x, 2) + std::pow(_vector.y, 2));
	}

	Vector2D normalize(Vector2D _vector)
	{
		float length = getLength(_vector);

		if (length != 0)
			_vector.x /= length, _vector.y /= length;

		return _vector;
	}

	Vector2D truncate(Vector2D _vector, float _max)
	{
		float mag = getLength(_vector);

		if (mag > _max)
			escalate(_vector, _max);

		return _vector;
	}

	void escalate(Vector2D _vector, float _scalar)
	{
		normalize(_vector);

		_vector.x *= _scalar, _vector.y *= _scalar;
	}
}