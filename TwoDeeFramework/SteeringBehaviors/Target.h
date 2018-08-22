#pragma once

#include "Vector2D.h"

namespace SB
{
	class Target
	{
	public:
		Target();
		~Target();

		Vector2D m_position;
		float m_arrivalRadius;
		float m_stopRadius;
	};
}