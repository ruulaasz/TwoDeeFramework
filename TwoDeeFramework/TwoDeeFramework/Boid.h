#pragma once

#include "Actor.h"
#include "Vector2D.h"

namespace TDF
{
	class Boid : public Actor
	{
	public:
		Boid();
		~Boid();

		Vector2D m_position;
		Vector2D m_velocity;
		float m_mass;
		float m_maxVelocity;
		Boid* m_target;
		Vector2D m_desiredVelocity;
		Vector2D m_steeringForce;

		float m_maxSeekForce;
		float m_seekScalar;

		float m_maxFleeForce;
		float m_fleeScalar;

		float m_maxArrivalForce;
		float m_arrivalScalar;
		float m_stopRadius;
		float m_arrivalRadius;

		float m_maxWanderForce;
		float m_wanderScalar;

		Vector2D m_circleCenter;
		float m_circleDistance;
		float m_circleRadius;
		float m_wanderAngle;

		float m_futureProjection;
		Vector2D m_futurePosition;
		float m_futureScale;

		float m_maxSeeAhead;
		float m_maxAvoidForce;

		void render();
	};
}