#include "AABB.h"
#include "RenderManager.h"

namespace TDF
{
	AABB::AABB()
	{

	}

	AABB::AABB(const Vector2D & _vector, float _width, float _height)
	{
		m_position = _vector;
		m_width = _width;
		m_height = _height;
	}

	AABB::~AABB()
	{

	}

	void AABB::render()
	{
		RenderManager::GetInstance().renderBox(*this);
	}
}