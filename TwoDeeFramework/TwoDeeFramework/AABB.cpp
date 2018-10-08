#include "AABB.h"
#include "RenderManager.h"

namespace TDF
{
	AABB::AABB()
	{
		m_width = 0;
		m_height = 0;
	}

	AABB::AABB(const Vector2D & _position, float _width, float _height)
	{
		m_position = _position;
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