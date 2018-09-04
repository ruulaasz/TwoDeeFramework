#pragma once

#include <vector>

#include "Actor.h"
#include "PathNode.h"
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
	  Vector2D m_renderDirection;
	  float m_mass;
	  float m_maxVelocity;
	  Boid* m_target;
	  Vector2D m_desiredVelocity;
	  Vector2D m_steeringForce;
	  float m_renderAngle;
	  
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
	  
	  bool m_loopPath;
	  std::vector<PathNode*> m_path;
	  
	  float m_trailDistance;
	  float m_separationRadius;
	  float m_maxSeparation;
	  float m_leaderSightRadius;
	  
	  int m_behaviors;
	  
	  void render();
	  void renderArrival();
	  void renderWander();
	  void renderPursuit();
	};
}