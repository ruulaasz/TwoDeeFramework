#include "PathNode.h"
#include "SDL_Manager.h"

namespace TDF
{
	PathNode::PathNode()
	{
		m_active = true;
	}

	PathNode::PathNode(Vector2D _position, float _radius)
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
		SDL_Manager::GetInstance().renderCircle(m_radius, m_position.x, m_position.y);
	}
}