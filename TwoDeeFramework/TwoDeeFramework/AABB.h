#pragma once

#include "Vector2D.h"

namespace TDF
{
	//!  An Axis Aligned bounding box class.
	class AABB
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		AABB();

		//! Secondary constructor.
		/*!
		Initialize the members of the class.
		\param _position a vector with the box position.
		\param _width the width of the box.
		\param _height the height of the box.
		*/
		AABB(const Vector2D& _position, float _width, float _height);

		//! Default destructor.
		~AABB();

		//! Render the box.
		void render();

	public:
		//! The box position.
		Vector2D m_position;

		//! The box width.
		float m_width;

		//! The box height.
		float m_height;
	};
}