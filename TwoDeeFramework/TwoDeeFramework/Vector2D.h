#pragma once

namespace TDF
{
	//!  A class for a 2D vector
	class Vector2D
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		explicit Vector2D(float _x = 0.f, float _y = 0.f);

		//! Default destructor.
		~Vector2D();

		//! Vector += Vector operator overload
		void operator+= (const Vector2D& _vector);

		//!  Vector *= Vector operator overload
		void operator*= (const Vector2D& _vector);

		//!  Vector - Vector operator overload
		Vector2D operator- (const Vector2D& _vector);

		//!  Vector + Vector operator overload
		Vector2D operator+ (const Vector2D& _vector);

		//! Vector * Vector operator overload
		Vector2D operator* (const Vector2D& _vector);

		//!  Vector * float operator overload
		Vector2D operator* (const float& _value);

		//!  Vector / float operator overload
		Vector2D operator/ (const float& _value);

		//! set the vector values to 0.
		void reset();

	public:
		float x;
		float y;
	};

	//! Computes the length of a 2D vector
	/*!
	\param _vector a to vector to get the lenght from
	\return a float with the lenght of the vector
	*/
	float getLength(const Vector2D& _vector);

	//! Normalize a 2D vector
	/*!
	\param _vector the vector to get normalized
	\return the normalized vector
	*/
	Vector2D normalize(const Vector2D& _vector);

	//! Truncates a vector
	/*!
	\param _vector the vector to get truncated
	\param _max the vector maximum length
	\return the truncated vector
	*/
	Vector2D truncate(const Vector2D& _vector, float _max);

	//! Escalate a vector
	/*!
	\param _vector the vector to get escalated
	\param _scalar the scale
	\return the escalated vector
	*/
	Vector2D escalate(const Vector2D& _vector, float _scalar);

	//! Rotates the vector to a given angle
	/*!
	\param _vector the vector to get rotated
	\param _angle the sngle of rotation
	\return the rotated vector
	*/
	Vector2D setAngle(const Vector2D& _vector, float _angle);
}