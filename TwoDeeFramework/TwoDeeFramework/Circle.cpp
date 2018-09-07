#include "Circle.h"
#include "RenderManager.h"

namespace TDF
{
	Circle::Circle()
	{

	}

	Circle::Circle(const Vector2D& _center, float _radius)
	{
		m_center = _center;
		m_radius = _radius;
	}

	Circle::~Circle()
	{

	}

	void TDF::Circle::render()
	{
		RenderManager::GetInstance().setRenderDrawColor(0, 0xFF, 0);
		TDF::RenderManager::GetInstance().renderCircle(m_radius, m_center.x, m_center.y);
	}
}