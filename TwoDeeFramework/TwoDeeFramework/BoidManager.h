#pragma once

#include <vector>
#include "Vector2D.h"
#include "Boid.h"
#include "Module.h"
#include "Circle.h"

namespace TDF
{
	//!  A enum for a behavior types.
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

	//!  A manager class for Boid behaviors. 
	class BoidManager : public Module<BoidManager>
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		BoidManager();

		//! Default destructor.
		~BoidManager();

		//! Compute the seek behavior
		/*!
		\param _me the boid to move.
		\param _targetPosition the position of the target
		\return the resultant force to move the boid.
		*/
		Vector2D seek(Boid* _me, Vector2D _targetPosition);

		//! Compute the flee behavior
		/*!
		\param _me the boid to move.
		\param _targetPosition the position of the target
		\return the resultant force to move the boid.
		*/
		Vector2D flee(Boid* _me, Vector2D _targetPosition);

		//! Compute the arrival behavior
		/*!
		\param _me the boid to move.
		\param _targetPosition the position of the target
		\param _radius the area of arrival effect.
		\return the resultant force to move the boid.
		*/
		Vector2D arrival(Boid* _me, Vector2D _targetPosition, float _radius);

		//! Compute the wander behavior
		/*!
		\param _me the boid to move.
		\return the resultant force to move the boid.
		*/
		Vector2D wander(Boid* _me);

		//! Compute the pursuit behavior
		/*!
		\param _me the boid to move.
		\param _targetPosition the position of the target
		\param _targetVelocity the velocity of the target
		\return the resultant force to move the boid.
		*/
		Vector2D pursuit(Boid* _me, Vector2D _targetPosition, Vector2D _targetVelocity);

		//! Compute the evade behavior
		/*!
		\param _me the boid to move.
		\param _targetPosition the position of the target
		\param _targetVelocity the velocity of the target
		\return the resultant force to move the boid.
		*/
		Vector2D evade(Boid* _me, Vector2D _targetPosition, Vector2D _targetVelocity);

		//! Compute the obstacle avoidance behavior
		/*!
		\param _me the boid to move.
		\return the resultant force to move the boid.
		*/
		Vector2D obstacleAvoidance(Boid* _me);

		//! Compute the follow path behavior
		/*!
		\param _me the boid to move.
		\param _path the points to follow.
		\return the resultant force to move the boid.
		*/
		Vector2D followPath(Boid* _me, std::vector<PathNode*> _path);

		//! Compute the follow leader behavior
		/*!
		\param _me the boid to move.
		\param _leader the boid to follow.
		\return the resultant force to move the boid.
		*/
		Vector2D followTheLeader(Boid* _me, Boid* _leader);

		//! Compute the separation behavior
		/*!
		\param _me the boid to move.
		\param _allBoids the boids to avoid.
		\return the resultant force to move the boid.
		*/
		Vector2D separation(Boid* _me, std::vector<Boid*> _allBoids);

		//! Updates all the boids
		/*!
		\param _deltaTime the change in time.
		*/
		void update(float _deltaTime);

		//! Renders all the boids
		void render();

	private:
		//! Finds the closest obstacle
		/*!
		\param _position of the boid.
		\param _ahead a proyection of the current position.
		\param _ahead2 a shorter proyection of the current position.
		\return the closest obstacle.
		*/
		Circle* findMostThreateningObstacle(Vector2D _position, 
											Vector2D _ahead, 
											Vector2D _ahead2);

		//! Finds if a line is touching the circle.
		/*!
		\param _ahead a proyection of the current position.
		\param _ahead2 a shorter proyection of the current position.
		\param _circle the circle to check
		\return if the linea is touching.
		*/
		bool lineIntersectCircle(Vector2D _ahead, Vector2D _ahead2, Circle* _circle);

		//! Get the distance between 2 coordenates.
		/*!
		\param _a a 2D vector.
		\param _b a second 2D vector
		\return the distance.
		*/
		float distanceBetween2Points(Vector2D _a, Vector2D _b);

		//! Finds if the leader is on sight.
		/*!
		\param _me the boid to move.
		\param _leader the boid to follow.
		\param _circle the circle to check
		\param _ahead a proyection of the current position.
		\return if the leader is on sight.
		*/
		bool isLeaderOnSight(Boid* _me, Boid* _leader, Vector2D _ahead);

	public:
		//! All active boids
		std::vector<Boid*> m_allBoids;

		//! All obstackes
		std::vector<TDF::Circle*> m_obstacles;

		//! Allowed total force.
		float m_maxTotalForce;
	};
}
