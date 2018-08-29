#include "Boid.h"
#include "SDL_Manager.h"

namespace TDF
{
	Boid::Boid()
	{
		m_maxVelocity = 2;
		m_mass = 50;

		m_maxSeekForce = 10;
		m_seekScalar = 1;

		m_maxFleeForce = 10;
		m_fleeScalar = 5;

		m_maxArrivalForce = 10;
		m_arrivalScalar = 1;
		m_stopRadius = 10;
		m_arrivalRadius = 200;

		m_maxWanderForce = 10;
		m_wanderScalar = 1;
		m_circleDistance = 100;
		m_circleRadius = 100;
		m_wanderAngle = 0;

		m_futureScale = 1;

		m_maxSeeAhead = 20;
		m_maxAvoidForce = 20;

		m_loopPath = false;

		m_trailDistance = 100;
		m_separationRadius = 60;
		m_maxSeparation = 200;
		m_leaderSightRadius =100;

		m_target = nullptr;
	}

	Boid::~Boid()
	{

	}

	void Boid::render()
	{
		Vector2D draw;

		draw = m_position + m_velocity * 15;
		SDL_SetRenderDrawColor(SDL_Manager::GetInstance().m_renderer, 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(SDL_Manager::GetInstance().m_renderer, m_position.x, m_position.y, draw.x , draw.y );

		draw = m_position + m_desiredVelocity * 15;
		SDL_SetRenderDrawColor(SDL_Manager::GetInstance().m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(SDL_Manager::GetInstance().m_renderer, m_position.x, m_position.y, draw.x, draw.y);

		for (size_t i = 0; i < m_path.size(); i++)
		{
			m_path.at(i)->render();
		}
	}
}