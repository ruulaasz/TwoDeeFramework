#include "CircleObstacle.h"
#include "SDL_Manager.h"

namespace TDF
{
	CircleObstacle::CircleObstacle()
	{

	}

	CircleObstacle::CircleObstacle(Vector2D _center, float _radius)
	{
		m_center = _center;
		m_radius = _radius;
	}

	CircleObstacle::~CircleObstacle()
	{

	}

	void TDF::CircleObstacle::render()
	{
		SDL_SetRenderDrawColor(TDF::SDL_Manager::GetInstance().m_renderer, 0, 0xFF, 0, SDL_ALPHA_OPAQUE);
		TDF::SDL_Manager::GetInstance().renderCircle(m_radius, m_center.x, m_center.y);
	}
}