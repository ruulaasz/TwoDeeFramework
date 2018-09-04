#pragma once
#include "Vector2D.h"

namespace TDF
{
	//!  A node to follow in boid behaviors
	class PathNode
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		\sa PathNode(Vector2D _position, float _radius);
		*/
		PathNode();

		//! Secondary constructor.
		/*!
		\param _position the node position
		\param _radius the node arrival radius
		\sa PathNode();
		*/
		PathNode(const Vector2D& _position, float _radius);

		//! Default destructor.
		~PathNode();


		//! Render the circle.
		void render();

		//! The node position.
		Vector2D m_position;

		//! The arrival radius.
		float m_radius;

		//! If has been visited.
		bool m_active;
	};
}