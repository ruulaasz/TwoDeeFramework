#include "BoidManager.h"
#include<cmath>
#include <time.h>

namespace TDF
{
	BoidManager::BoidManager()
	{
		m_maxTotalForce = 40;

		srand(time_t(NULL));
	}

	BoidManager::~BoidManager()
	{

	}

	Vector2D BoidManager::seek(Boid* _me, Vector2D _targetPosition)
	{
		_me->m_desiredVelocity = normalize(_targetPosition - _me->m_position) * _me->m_maxVelocity;
		Vector2D seekForce = (_me->m_desiredVelocity - _me->m_velocity) * _me->m_seekScalar;
		seekForce = truncate(seekForce, _me->m_maxSeekForce);

		return seekForce;
	}

	Vector2D BoidManager::flee(Boid * _me, Vector2D _targetPosition)
	{
		_me->m_desiredVelocity = normalize(_me->m_position - _targetPosition) * _me->m_maxVelocity;
		Vector2D fleeForce = (_me->m_desiredVelocity - _me->m_velocity) * _me->m_fleeScalar;
		fleeForce = truncate(fleeForce, _me->m_maxFleeForce);

		return fleeForce;
	}

	Vector2D BoidManager::arrival(Boid * _me, Vector2D _targetPosition, float _radius)
	{
		_me->m_desiredVelocity = normalize(_targetPosition - _me->m_position) * _me->m_maxVelocity;
		Vector2D seekForce = (_me->m_desiredVelocity - _me->m_velocity) * _me->m_seekScalar;
		seekForce = truncate(seekForce, _me->m_maxSeekForce);

		_me->m_desiredVelocity = _targetPosition - _me->m_position;
		float distanceToTarget = getLength(_me->m_desiredVelocity);
		_me->m_desiredVelocity = normalize(_me->m_desiredVelocity);

		if (distanceToTarget < _radius)
		{
			_me->m_desiredVelocity = normalize(_me->m_desiredVelocity) * _me->m_maxVelocity * (distanceToTarget / _radius);
		}
		else
		{
			_me->m_desiredVelocity = normalize(_me->m_desiredVelocity) * _me->m_maxVelocity;
		}

		Vector2D arrivalForce = (_me->m_desiredVelocity - _me->m_velocity) * _me->m_arrivalScalar;
		arrivalForce = truncate(arrivalForce, _me->m_maxArrivalForce);

		if (distanceToTarget < _me->m_stopRadius)
		{
			_me->m_velocity.x = 0;
			_me->m_velocity.y = 0;

			seekForce.x = 0;
			seekForce.y = 0;
		}

		return arrivalForce + seekForce;
	}

	Vector2D BoidManager::wander(Boid* _me)
	{
		_me->m_circleCenter = _me->m_velocity;
		_me->m_circleCenter = normalize(_me->m_circleCenter);
		_me->m_circleCenter = escalate(_me->m_circleCenter, _me->m_circleDistance);

		Vector2D displacement = Vector2D(0, -1);
		displacement = escalate(displacement, _me->m_circleRadius);

		displacement = setAngle(displacement, _me->m_wanderAngle);

		_me->m_wanderAngle = static_cast<float>(rand() % 360);
		_me->m_wanderAngle = _me->m_wanderAngle * static_cast<float>(3.141592 / 180);

		Vector2D m_wanderForce = (_me->m_circleCenter + displacement) * _me->m_wanderScalar;
		m_wanderForce = truncate(m_wanderForce, _me->m_maxWanderForce);

		return m_wanderForce;
	}

	Vector2D BoidManager::pursuit(Boid * _me, Vector2D _targetPosition, Vector2D _targetVelocity)
	{
		Vector2D distanceToTarget = _targetPosition - _me->m_position;
		_me->m_futureProjection = (getLength(distanceToTarget) / _me->m_maxVelocity) * _me->m_futureScale;
		_me->m_futurePosition = _targetPosition + _targetVelocity * _me->m_futureProjection;

		return seek(_me, _me->m_futurePosition);
	}

	Vector2D BoidManager::evade(Boid * _me, Vector2D _targetPosition, Vector2D _targetVelocity)
	{
		Vector2D distanceToTarget = _targetPosition - _me->m_position;
		_me->m_futureProjection = (getLength(distanceToTarget) / _me->m_maxVelocity) * _me->m_futureScale;
		_me->m_futurePosition = _targetPosition + _targetVelocity * _me->m_futureProjection;

		return flee(_me, _me->m_futurePosition);
	}

	Vector2D BoidManager::obstacleAvoidance(Boid* _me)
	{
		float dynamicLength = getLength(_me->m_velocity) / _me->m_maxVelocity;

		Vector2D ahead = _me->m_position + normalize(_me->m_velocity) * _me->m_maxSeeAhead;
		Vector2D ahead2 = _me->m_position + normalize(_me->m_velocity) * _me->m_maxSeeAhead * 0.5;

		CircleObstacle* mostThreatening = findMostThreateningObstacle(_me->m_position, ahead, ahead2);

		Vector2D avoidance;

		if (mostThreatening != nullptr) 
		{
			avoidance.x = ahead.x - mostThreatening->m_center.x;
			avoidance.y = ahead.y - mostThreatening->m_center.y;

			normalize(avoidance);
			escalate(avoidance, _me->m_maxAvoidForce);
		}
		else 
		{
			escalate(avoidance, 0); // nullify the avoidance force
		}

		return avoidance;
	}

	CircleObstacle* BoidManager::findMostThreateningObstacle(Vector2D _position, Vector2D _ahead, Vector2D _ahead2)
	{
		CircleObstacle* mostThreatening = nullptr;

		for (size_t i=0;i < m_obstacles.size(); i++)
		{
			CircleObstacle* Obstacle = m_obstacles.at(i);
			bool collision = lineIntersectCircle(_ahead, _ahead2, Obstacle);

			// "position" is the character's current position
			if (collision && (mostThreatening == nullptr || distanceBetween2Points(_position, Obstacle->m_center) < distanceBetween2Points(_position, mostThreatening->m_center))) 
			{
				mostThreatening = Obstacle;
			}
		}
		return mostThreatening;
	}

	bool BoidManager::lineIntersectCircle(Vector2D _ahead, Vector2D _ahead2, CircleObstacle* _circle)
	{
		return distanceBetween2Points(_circle->m_center, _ahead) <= _circle->m_radius || distanceBetween2Points(_circle->m_center, _ahead2) <= _circle->m_radius;
	}

	float BoidManager::distanceBetween2Points(Vector2D _a, Vector2D _b)
	{
		return std::sqrt((_a.x - _b.x) * (_a.x - _b.x) + (_a.y - _b.y) * (_a.y - _b.y));
	}

	void BoidManager::update(float _deltaTime)
	{
		for (size_t i = 0; i < m_allBoids.size(); i++)
		{
			Boid* boid = m_allBoids.at(i);

			boid->m_steeringForce = arrival(boid, boid->m_target->m_position, boid->m_target->m_arrivalRadius) + obstacleAvoidance(boid);

			boid->m_steeringForce = truncate(boid->m_steeringForce, m_maxTotalForce);
			boid->m_steeringForce = boid->m_steeringForce / boid->m_mass;

			boid->m_velocity = boid->m_velocity + boid->m_steeringForce;
			boid->m_velocity = truncate(boid->m_velocity, boid->m_maxVelocity);

			boid->m_position += boid->m_velocity;
		}
	}

	void BoidManager::render()
	{
		for (size_t i = 0; i < m_allBoids.size(); i++)
		{
			Boid* boid = m_allBoids.at(i);
			boid->render();
		}
	}
}