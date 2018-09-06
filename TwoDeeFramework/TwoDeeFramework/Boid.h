#pragma once

#include <vector>
#include "Actor.h"
#include "PathNode.h"
#include "Vector2D.h"

namespace TDF
{
	//!  A class for a boid actor
	class Boid : public Actor
	{
	 public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Boid();

		//! Default destructor.
		~Boid();

		virtual void update(float _deltaTime) {};
		virtual void render() {};
		virtual void init() {};
		virtual void onEnterCollision(int _tag) {};

		//! render the debug lines.
		void renderVectors();

		//! render the arrival behavior.
		void renderArrival();

		//! render the wander behavior.
		void renderWander();

		//! render the pursuit behavior.
		void renderPursuit();

		//general boid variables
		Vector2D m_position;
		Vector2D m_velocity;
		float m_mass;
		float m_maxVelocity;
		Boid* m_target;
		Vector2D m_desiredVelocity;
		Vector2D m_steeringForce;
		float m_renderAngle;
		int m_behaviors;
		Vector2D m_renderDirection;

		//seek parameters
		float m_maxSeekForce;
		float m_seekScalar;
		
		//flee parameters
		float m_maxFleeForce;
		float m_fleeScalar;
		
		//arrival parameters
		float m_maxArrivalForce;
		float m_arrivalScalar;
		float m_stopRadius;
		float m_arrivalRadius;
		
		//wander parameters
		float m_maxWanderForce;
		float m_wanderScalar;
		Vector2D m_circleCenter;
		float m_circleDistance;
		float m_circleRadius;
		float m_wanderAngle;
		
		//pursuit & evade parameters
		float m_futureProjection;
		Vector2D m_futurePosition;
		float m_futureScale;

		//obstacle avoidance parameters
		float m_maxSeeAhead;
		float m_maxAvoidForce;
		
		//followpath parameters
		bool m_loopPath;
		std::vector<PathNode*> m_path;
		
		//follow the leader parameters
		float m_trailDistance;
		float m_separationRadius;
		float m_maxSeparation;
		float m_leaderSightRadius;
	};
}