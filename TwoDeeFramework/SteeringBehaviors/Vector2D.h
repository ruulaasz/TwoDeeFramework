#pragma once

namespace SB
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

	public:
		float x;
		float y;
	};

	float getLength(Vector2D _vector);
	Vector2D normalize(Vector2D _vector);
	Vector2D truncate(Vector2D _vector, float _max);
	void escalate(Vector2D _vector, float _scalar);
}