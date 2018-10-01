#include "Vector2D.h"
#include <cmath>

namespace TDF
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

	void Vector2D::reset()
	{
		x = 0;
		y = 0;
	}

	float getLength(const Vector2D& _vector)
	{
		return sqrt(pow(_vector.x, 2) + pow(_vector.y, 2));
	}

	Vector2D normalize(const Vector2D& _vector)
	{
		Vector2D result;

		float length = getLength(_vector);

		if (length != 0)
		{
			result.x = _vector.x / length;
			result.y = _vector.y / length;
			return result;
		}
			
		return _vector;
	}

	Vector2D truncate(const Vector2D& _vector, float _max)
	{
		Vector2D result;

		if (getLength(_vector) > _max)
		{
			result = escalate(_vector, _max);
			return result;
		}

		return _vector;
	}

	Vector2D escalate(const Vector2D& _vector, float _scalar)
	{
		Vector2D result;

		result = normalize(_vector);

		result.x *= _scalar, result.y *= _scalar;

		return result;
	}

	Vector2D setAngle(const Vector2D& _vector, float _angle)
	{
		float length = getLength(_vector);

		Vector2D result;

		result.x = cos(_angle) * length;
		result.y = sin(_angle) * length;

		return result;
	}
}