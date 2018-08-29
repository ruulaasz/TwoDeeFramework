#pragma once
#include "Vector2D.h"

namespace TDF
{
	class PathNode
	{
	public:
		PathNode();
		PathNode(Vector2D _position, float _radius);
		~PathNode();

		Vector2D m_position;
		float m_radius;
		bool m_active;

		void render();
	};
}