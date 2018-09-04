#pragma once

#include "Vector2D.h"

namespace TDF
{
	//!  An obstacle for boid behaviors
	class CircleObstacle
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		\sa CircleObstacle(Vector2D _center, float _radius);
		*/
		CircleObstacle();

		//! Secondary constructor.
		/*!
		\param _center the circle position
		\param _radius the circle radius
		\sa CircleObstacle();
		*/
		CircleObstacle(const Vector2D& _center, float _radius);

		//! Default destructor.
		~CircleObstacle();

		//! Render the circle.
		void render();

		//! The circle position.
		Vector2D m_center;

		//! The circle radius.
		float m_radius;
	};
}