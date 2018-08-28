#pragma once

#include "Vector2D.h"

namespace TDF
{
	class CircleObstacle
	{
	public:
		CircleObstacle();
		CircleObstacle(Vector2D _center, float _radius);
		~CircleObstacle();

		Vector2D m_center;
		float m_radius;

		void render();
	};
}