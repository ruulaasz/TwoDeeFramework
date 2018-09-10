#pragma once

#include "Vector2D.h"

namespace TDF
{
	//!  An obstacle for boid behaviors
	class Circle
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		\sa Circle(Vector2D _center, float _radius);
		*/
		Circle();

		//! Secondary constructor.
		/*!
		\param _center the circle position
		\param _radius the circle radius
		\sa Circle();
		*/
		Circle(const Vector2D& _center, float _radius);

		//! Default destructor.
		~Circle();

		//! Render the circle.
		void render();

	public:
		//! The circle position.
		Vector2D m_center;

		//! The circle radius.
		float m_radius;
	};
}