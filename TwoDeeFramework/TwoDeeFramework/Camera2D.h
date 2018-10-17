#pragma once

#include "AABB.h"

namespace TDF
{
	class Actor;

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		AABB m_areaBox;
	};
}