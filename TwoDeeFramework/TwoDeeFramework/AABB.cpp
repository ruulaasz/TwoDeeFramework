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

	float AABB::left()
	{
		return m_position.x;
	}

	float AABB::right()
	{
		return m_position.x + m_width;
	}

	float AABB::bottom()
	{
		return m_position.y + m_height;
	}

	float AABB::top()
	{
		return m_position.y;
	}
}