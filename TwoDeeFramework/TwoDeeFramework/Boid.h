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

		//! Update the actor.
		/*!
		\param _deltaTime the change of time.
		*/
		virtual void update(float _deltaTime) { _deltaTime; };

		//! Render the actor.
		virtual void render();

		//! Initialize the actor.
		virtual void init() {};

		//! Collision with something.
		/*!
		\param _tag the id of the collided object.
		*/
		virtual void onEnterCollision(int _tag) { _tag; };

		//! Dispatch a recieved message.
		/*!
		\param _message the receieved message.
		*/
		virtual void dispatchMessage(const TDF::InputMessage& _message) { _message; };

		//! render the arrival behavior.
		void renderArrival();

		//! render the wander behavior.
		void renderWander();

		//! render the pursuit behavior.
		void renderPursuit();

	public:
		//! General boid atributes.
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

		//! Seek parameters
		float m_maxSeekForce;
		float m_seekScalar;
		
		//! Flee parameters
		float m_maxFleeForce;
		float m_fleeScalar;
		
		//! Arrival parameters
		float m_maxArrivalForce;
		float m_arrivalScalar;
		float m_stopRadius;
		float m_arrivalRadius;
		
		//! Wander parameters
		float m_maxWanderForce;
		float m_wanderScalar;
		Vector2D m_circleCenter;
		float m_circleDistance;
		float m_circleRadius;
		float m_wanderAngle;
		
		//! Pursuit & evade parameters
		float m_futureProjection;
		Vector2D m_futurePosition;
		float m_futureScale;

		//! Obstacle avoidance parameters
		float m_maxSeeAhead;
		float m_maxAvoidForce;
		
		//! Followpath parameters
		bool m_loopPath;
		std::vector<PathNode*> m_path;
		
		//! Follow the leader parameters
		float m_trailDistance;
		float m_separationRadius;
		float m_maxSeparation;
		float m_leaderSightRadius;
	};
}