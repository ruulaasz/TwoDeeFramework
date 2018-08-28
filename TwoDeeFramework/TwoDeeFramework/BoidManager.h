#pragma once

#include "Vector2D.h"
#include "Boid.h"
#include <vector>
#include "Module.h"
#include "CircleObstacle.h"

namespace TDF
{
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

		CircleObstacle* findMostThreateningObstacle(Vector2D _position, Vector2D _ahead, Vector2D _ahead2);
		bool lineIntersectCircle(Vector2D _ahead, Vector2D _ahead2, CircleObstacle* _circle);
		float distanceBetween2Points(Vector2D _a, Vector2D _b);

		void update(float _deltaTime);
		void render();

		std::vector<Boid*> m_allBoids;
		std::vector<TDF::CircleObstacle*> m_obstacles;
	};
}
