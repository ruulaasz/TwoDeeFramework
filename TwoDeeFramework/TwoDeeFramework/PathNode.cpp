#include "PathNode.h"
#include "RenderManager.h"

namespace TDF
{
	PathNode::PathNode()
	{
		m_active = true;
		m_radius = 0;
	}

	PathNode::PathNode(const Vector2D& _position, float _radius)
	{
		m_radius = _radius;
		m_position = _position;
		m_active = true;
	}

	PathNode::~PathNode()
	{

	}

	void PathNode::render()
	{
		RenderManager::GetInstance().renderCircle(m_radius, m_position.x, m_position.y);
	}
}