#include "BoidManager.h"
#include <cmath>
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
		Vector2D seekForce = seek(_me, _targetPosition);

		_me->m_desiredVelocity = _targetPosition - _me->m_position;
		float distanceToTarget = getLength(_me->m_desiredVelocity);
		_me->m_desiredVelocity = normalize(_me->m_desiredVelocity);

		if (distanceToTarget < _radius)
		{
			_me->m_desiredVelocity = normalize(_me->m_desiredVelocity) * 
											   _me->m_maxVelocity * 
											   (distanceToTarget / _radius);
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

			arrivalForce.x = 0;
			arrivalForce.y = 0;
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

		_me->m_futureProjection = (getLength(distanceToTarget) / _me->m_maxVelocity) * 
								   _me->m_futureScale;

		_me->m_futurePosition = _targetPosition + _targetVelocity * _me->m_futureProjection;

		return seek(_me, _me->m_futurePosition);
	}

	Vector2D BoidManager::evade(Boid * _me, Vector2D _targetPosition, Vector2D _targetVelocity)
	{
		Vector2D distanceToTarget = _targetPosition - _me->m_position;

		_me->m_futureProjection = (getLength(distanceToTarget) / _me->m_maxVelocity) * 
								   _me->m_futureScale;

		_me->m_futurePosition = _targetPosition + _targetVelocity * _me->m_futureProjection;

		return flee(_me, _me->m_futurePosition);
	}

	Vector2D BoidManager::obstacleAvoidance(Boid* _me)
	{
		//float dynamicLength = getLength(_me->m_velocity) / _me->m_maxVelocity;

		Vector2D ahead = _me->m_position + normalize(_me->m_velocity) * _me->m_maxSeeAhead;
		Vector2D ahead2 = _me->m_position + normalize(_me->m_velocity) * _me->m_maxSeeAhead * 0.5;

		Circle* mostThreatening = findMostThreateningObstacle(_me->m_position,
																	   ahead, 
																	   ahead2);

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
			escalate(avoidance, 0);
		}

		return avoidance;
	}

	Vector2D BoidManager::followPath(Boid * _me, std::vector<PathNode*> _path)
	{
		float distanceToTarget;
		Vector2D arrivalForce;

		for (size_t i = 0; i < _path.size(); i++)
		{
			if (_path.at(i)->m_active)
			{
				if (i == _path.size() - 1 && !_me->m_loopPath)
				{
					arrivalForce = arrival(_me, 
										   _path.at(_path.size() - 1)->m_position, 
										   _path.at(_path.size() - 1)->m_radius);

					if (getLength(arrivalForce) <= 0)
					{
						_path.at(i)->m_active = false;
					}

					return arrivalForce;
				}

				_me->m_desiredVelocity = _path.at(i)->m_position - _me->m_position;
				distanceToTarget = getLength(_me->m_desiredVelocity);

				if (distanceToTarget > _path.at(i)->m_radius)
				{
					return seek(_me, _path.at(i)->m_position);
				}
				else
				{
					_path.at(i)->m_active = false;
				}
			}
		}

		if (_me->m_loopPath)
		{
			for (size_t i = 0; i < _path.size(); i++)
			{
				_path.at(i)->m_active = true;
			}

			return seek(_me, _path.at(0)->m_position);
		}

		return Vector2D();
	}

	Vector2D BoidManager::followTheLeader(Boid * _me, Boid * _leader)
	{
		Vector2D force;

		Vector2D tv = normalize(_leader->m_velocity);
		tv = tv * _me->m_trailDistance;

		Vector2D ahead = _leader->m_position + tv;

		tv = tv * -1;
		Vector2D behind = _leader->m_position + tv;

		if (isLeaderOnSight(_me, _leader, ahead)) 
		{
			force += evade(_me, _leader->m_position, _leader->m_velocity);
		}

		force += arrival(_me, behind, _leader->m_arrivalRadius);

		force += separation(_me, m_allBoids);

		return force;
	}

	Vector2D BoidManager::separation(Boid * _me, std::vector<Boid*> _allBoids)
	{
		int neighborCount = 0;
		Boid* boid;
		Vector2D force;
		Vector2D alligment;
		Vector2D cohesion;

		for (size_t i = 0; i < _allBoids.size(); i++)
		{
			boid = _allBoids.at(i);

			if (boid != _me && 
				distanceBetween2Points(boid->m_position, _me->m_position) <= 
				_me->m_separationRadius)
			{
				//Alignment
				alligment.x += boid->m_velocity.x;
				alligment.y += boid->m_velocity.y;

				//cohesion
				cohesion.x += boid->m_position.x;
				cohesion.y += boid->m_position.y;
				cohesion = Vector2D(cohesion.x - boid->m_position.x, cohesion.y - boid->m_position.y);

				force += (boid->m_position - _me->m_position);
				neighborCount++;
			}
		}

		if (neighborCount != 0) 
		{
			//Alignment
			alligment.x /= neighborCount;
			alligment.y /= neighborCount;
			normalize(alligment);

			//cohesion
			cohesion.x /= neighborCount;
			cohesion.y /= neighborCount;
			normalize(cohesion);

			force.x /= neighborCount;
			force.y /= neighborCount;

			force.x *= -1;
			force.y *= -1;
		}

		escalate(force, _me->m_maxSeparation);

		//alligmentcoheison
		_me->m_velocity += alligment;
		_me->m_velocity += cohesion;

		return force;
	}

	Circle* BoidManager::findMostThreateningObstacle(Vector2D _position, Vector2D _ahead, Vector2D _ahead2)
	{
		Circle* mostThreatening = nullptr;
		Circle* Obstacle;

		for (size_t i=0;i < m_obstacles.size(); i++)
		{
			Obstacle = m_obstacles.at(i);
			bool collision = lineIntersectCircle(_ahead, _ahead2, Obstacle);

			if (collision && 
				(mostThreatening == nullptr || 
				 distanceBetween2Points(_position, Obstacle->m_center) < 
				 distanceBetween2Points(_position, mostThreatening->m_center))) 
			{
				mostThreatening = Obstacle;
			}
		}
		return mostThreatening;
	}

	bool BoidManager::lineIntersectCircle(Vector2D _ahead, Vector2D _ahead2, Circle* _circle)
	{
		return distanceBetween2Points(_circle->m_center, _ahead) <= 
									  _circle->m_radius || 
									  distanceBetween2Points(_circle->m_center, _ahead2) <= 
									  _circle->m_radius;
	}

	float BoidManager::distanceBetween2Points(Vector2D _a, Vector2D _b)
	{
		return std::sqrt((_a.x - _b.x) * (_a.x - _b.x) + (_a.y - _b.y) * (_a.y - _b.y));
	}

	bool BoidManager::isLeaderOnSight(Boid* _me, Boid * _leader, Vector2D _ahead)
	{
		return distanceBetween2Points(_ahead, _me->m_position) <= 
									  _leader->m_leaderSightRadius ||
									  distanceBetween2Points(_leader->m_position, _me->m_position) <= 
									 _leader->m_leaderSightRadius;
	}

	void BoidManager::update(float _deltaTime)
	{
		_deltaTime;

		for (size_t i = 0; i < m_allBoids.size(); i++)
		{
			Boid* boid = m_allBoids.at(i);
			boid->m_steeringForce.reset();

			if (boid->m_behaviors & BT_SEEK)
			{
				boid->m_steeringForce += seek(boid, boid->m_target->m_position);
			}

			if (boid->m_behaviors & BT_FLEE)
			{
				boid->m_steeringForce += flee(boid, boid->m_target->m_position);
			}

			if (boid->m_behaviors & BT_ARRIVAL)
			{
				boid->m_steeringForce += arrival(boid, 
												 boid->m_target->m_position, 
												 boid->m_target->m_arrivalRadius);
			}

			if (boid->m_behaviors & BT_WANDER)
			{
				boid->m_steeringForce += wander(boid);
			}

			if (boid->m_behaviors & BT_PURSUIT)
			{
				boid->m_steeringForce += pursuit(boid, 
												 boid->m_target->m_position, 
												 boid->m_target->m_velocity);
			}

			if (boid->m_behaviors & BT_EVADE)
			{
				boid->m_steeringForce += evade(boid, 
											   boid->m_target->m_position, 
											   boid->m_target->m_velocity);
			}

			if (boid->m_behaviors & BT_OBSTACLE)
			{
				boid->m_steeringForce += obstacleAvoidance(boid);
			}

			if (boid->m_behaviors & BT_FOLLOWPATH)
			{
				boid->m_steeringForce += followPath(boid, boid->m_path);
			}

			if (boid->m_behaviors & BT_FOLLOWLEADER)
			{
				boid->m_steeringForce += followTheLeader(boid, boid->m_target);
			}

			if (boid->m_behaviors & BT_SEPARATION)
			{
				boid->m_steeringForce += separation(boid, m_allBoids);
			}

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

			if (boid->m_behaviors & BT_ARRIVAL)
			{
				boid->renderArrival();
			}

			if (boid->m_behaviors & BT_WANDER)
			{
				boid->renderWander();
			}

			if (boid->m_behaviors & BT_PURSUIT)
			{
				boid->renderPursuit();
			}

			if (boid->m_behaviors & BT_EVADE)
			{
				boid->renderPursuit();
			}
		}
	}
}