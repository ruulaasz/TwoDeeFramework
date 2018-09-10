#include "Boid.h"
#include "RenderManager.h"

#define DEBUGLINE_LENGTH 15

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
	  m_arrivalRadius = 100;
	  
	  m_maxWanderForce = 10;
	  m_wanderScalar = 1;
	  m_circleDistance = 100;
	  m_circleRadius = 100;
	  m_wanderAngle = 0;
	  
	  m_futureScale = 0.7f;
	  
	  m_maxSeeAhead = 20;
	  m_maxAvoidForce = 20;
	  
	  m_loopPath = false;
	  
	  m_trailDistance = 100;
	  m_separationRadius = 60;
	  m_maxSeparation = 200;
	  m_leaderSightRadius =100;
	  
	  m_target = nullptr;

	  m_renderAngle = 0;
	  m_behaviors = 0;
	  m_futureProjection = 0;
	}

	Boid::~Boid()
	{

	}

	void Boid::render()
	{
		Vector2D lineEnd;

		if (getLength(m_velocity) > 0)
		{
			m_renderDirection = m_velocity;
		}

		m_renderAngle = static_cast<float>(std::atan2(m_renderDirection.x,
													 -m_renderDirection.y));

		lineEnd = m_position + m_velocity * DEBUGLINE_LENGTH;

		RenderManager::GetInstance().setRenderDrawColor(0xFF, 0, 0);

		SDL_RenderDrawLine(SDL_Manager::GetInstance().m_renderer,
													  static_cast<int>(m_position.x),
													  static_cast<int>(m_position.y),
													  static_cast<int>(lineEnd.x),
													  static_cast<int>(lineEnd.y));

		lineEnd = m_position + m_desiredVelocity * DEBUGLINE_LENGTH;

		RenderManager::GetInstance().setRenderDrawColor(0, 0, 0);

		SDL_RenderDrawLine(SDL_Manager::GetInstance().m_renderer,
													  static_cast<int>(m_position.x),
													  static_cast<int>(m_position.y),
													  static_cast<int>(lineEnd.x),
													  static_cast<int>(lineEnd.y));

		for (size_t i = 0; i < m_path.size(); i++)
		{
			m_path.at(i)->render();
		}
	}

	void Boid::renderArrival()
	{
		RenderManager::GetInstance().setRenderDrawColor(0, 0xFF, 0);
		RenderManager::GetInstance().renderCircle(m_arrivalRadius, m_position.x, m_position.y);
		RenderManager::GetInstance().renderCircle(m_stopRadius, m_position.x, m_position.y);
	}

	void Boid::renderWander()
	{
		RenderManager::GetInstance().setRenderDrawColor(0, 0xFF, 0);

		RenderManager::GetInstance().renderCircle(m_circleRadius,
												  m_circleCenter.x + m_position.x, 
												  m_circleCenter.y + m_position.y);
	}

	void Boid::renderPursuit()
	{
		RenderManager::GetInstance().setRenderDrawColor(0, 0xFF, 0);
		RenderManager::GetInstance().renderCircle(10, m_futurePosition.x, m_futurePosition.y);
	}
}