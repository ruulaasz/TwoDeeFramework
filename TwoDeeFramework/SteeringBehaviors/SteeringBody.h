#pragma once

#include "Target.h"

namespace SB
{
	enum BehaviorType
	{
		BT_SEEK = 0,
		BT_FLEE,
		BT_ARRIVALSEEK,
		BT_WANDER,
		BT_NONE
	};

	class SteeringBody
	{
	public:
		SteeringBody();
		~SteeringBody();

		void update(float _deltaTime);
		void setTarget(Target* _target);

	public:
		Vector2D m_position;
		Vector2D m_velocity;
		float m_maxVelocity;
		Vector2D m_finalForce;
		Vector2D m_desiredVelocity;

		float m_mass;
		float m_distanceToTarget;
		BehaviorType m_type;
		Target* m_target;

		Vector2D m_seekForce;
		float m_maxSeekForce;
		float m_seekScalar;

		Vector2D m_fleeForce;
		float m_maxFleeForce;
		float m_fleeScalar;

		Vector2D m_arrivalForce;
		float m_maxArrivalForce;
		float m_arrivalScalar;
	};
}