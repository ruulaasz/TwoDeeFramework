#pragma once

namespace TDF
{
	class Vector2D
	{
	public:
		explicit Vector2D(float _x = 0.f, float _y = 0.f);
		~Vector2D();

		void operator+= (const Vector2D& _vector);
		void operator*= (const Vector2D& _vector);
		Vector2D operator- (const Vector2D& _vector);
		Vector2D operator+ (const Vector2D& _vector);
		Vector2D operator* (const Vector2D& _vector);
		Vector2D operator* (const float& _value);
		Vector2D operator/ (const float& _value);

		void reset();

	public:
		float x;
		float y;
	};

	float getLength(Vector2D _vector);
	Vector2D normalize(Vector2D _vector);
	Vector2D truncate(Vector2D _vector, float _max);
	Vector2D escalate(Vector2D _vector, float _scalar);
	Vector2D setAngle(Vector2D _vector, float _scalar);
}