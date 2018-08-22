#include "SteeringBody.h"

namespace SB
{
	SteeringBody::SteeringBody()
	{
		m_maxSeekForce = 10;
		m_seekScalar = 1;

		m_maxFleeForce = 10;
		m_fleeScalar = 1;

		m_maxArrivalForce = 10;
		m_arrivalScalar = 1;

		m_maxVelocity = 1;
		m_mass = 50;
		m_type = BT_NONE;
		m_target = new Target();
	}

	SteeringBody::~SteeringBody()
	{

	}

	void SteeringBody::update(float _deltaTime)
	{
		switch (m_type)
		{
		default:
			break;

		case BT_SEEK:
			m_desiredVelocity = normalize(m_target->m_position - m_position) * m_maxVelocity;
			m_seekForce = (m_desiredVelocity - m_velocity) * m_seekScalar;
			m_seekForce = truncate(m_seekForce, m_maxSeekForce);
			break;

		case BT_FLEE:
			m_desiredVelocity = normalize(m_position - m_target->m_position) * m_maxVelocity;
			m_fleeForce = (m_desiredVelocity - m_velocity) * m_fleeScalar;
			m_fleeForce = truncate(m_fleeForce, m_maxFleeForce);
			break;

		case BT_ARRIVALSEEK:
			m_desiredVelocity = normalize(m_target->m_position - m_position) * m_maxVelocity;
			m_seekForce = (m_desiredVelocity - m_velocity) * m_seekScalar;
			m_seekForce = truncate(m_seekForce, m_maxSeekForce);

			m_desiredVelocity = m_target->m_position - m_position;
			m_distanceToTarget = getLength(m_desiredVelocity);

			if (m_distanceToTarget < m_target->m_arrivalRadius)
			{
				m_desiredVelocity = normalize(m_desiredVelocity) * m_maxVelocity * (m_distanceToTarget / m_target->m_arrivalRadius);
			}
			else
			{
				m_desiredVelocity = normalize(m_desiredVelocity) * m_maxVelocity;
			}

			m_arrivalForce = (m_desiredVelocity - m_velocity) * m_arrivalScalar;
			m_arrivalForce = truncate(m_arrivalForce, m_maxArrivalForce);

			if (m_distanceToTarget < m_target->m_stopRadius)
			{
				m_velocity.x = 0;
				m_velocity.y = 0;

				m_seekForce.x = 0;
				m_seekForce.y = 0;
			}
			break;
		}

		m_finalForce = m_seekForce + m_arrivalForce + m_fleeForce;
		m_finalForce = m_finalForce / m_mass;

		m_velocity = truncate(m_velocity + m_finalForce, m_maxVelocity);

		m_position += m_velocity;
	}

	void SteeringBody::setTarget(Target* _target)
	{
		m_target = _target;
	}
}