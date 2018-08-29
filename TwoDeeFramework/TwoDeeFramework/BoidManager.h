#pragma once

#include "Vector2D.h"
#include "Boid.h"
#include <vector>
#include "Module.h"
#include "CircleObstacle.h"

namespace TDF
{
	enum BehaviorType
	{
		BT_SEEK = 0x01,
		BT_FLEE = 0x02,
		BT_ARRIVAL = 0x04,
		BT_WANDER = 0x08,
		BT_PURSUIT = 0x10,
		BT_EVADE = 0x20,
		BT_OBSTACLE = 0x40,
		BT_FOLLOWPATH = 0x80,
		BT_FOLLOWLEADER = 0x100,
		BT_SEPARATION = 0x200,
		BT_NONE
	};

	class BoidManager : public Module<BoidManager>
	{
	public:
		BoidManager();
		~BoidManager();

		float m_maxTotalForce;

		Vector2D seek(Boid* _me, Vector2D _targetPosition);
		Vector2D flee(Boid* _me, Vector2D _targetPosition);
		Vector2D arrival(Boid* _me, Vector2D _targetPosition, float _radius);
		Vector2D wander(Boid* _me);
		Vector2D pursuit(Boid* _me, Vector2D _targetPosition, Vector2D _targetVelocity);
		Vector2D evade(Boid* _me, Vector2D _targetPosition, Vector2D _targetVelocity);
		Vector2D obstacleAvoidance(Boid* _me);
		Vector2D followPath(Boid* _me, std::vector<PathNode*> _path);
		Vector2D followTheLeader(Boid* _me, Boid* _leader);
		Vector2D separation(Boid* _me, std::vector<Boid*> _allBoids);

		CircleObstacle* findMostThreateningObstacle(Vector2D _position, Vector2D _ahead, Vector2D _ahead2);
		bool lineIntersectCircle(Vector2D _ahead, Vector2D _ahead2, CircleObstacle* _circle);
		float distanceBetween2Points(Vector2D _a, Vector2D _b);
		bool isLeaderOnSight(Boid* _me, Boid* _leader, Vector2D _ahead);
		Vector2D alligmentCohesion();

		void update(float _deltaTime);
		void render();

		std::vector<Boid*> m_allBoids;
		std::vector<TDF::CircleObstacle*> m_obstacles;
	};
}
