#pragma once

#include "StdHeaders.h"
#include "Box2DManager.h"

namespace TDF
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld();

		void update();
		void render();
		void init(String _worldName = "earth");
		void init(b2World* _world);

		//! The physiscs of the world.
		b2World* m_world;

	private:
		//! The length of time passed to simulate (seconds).
		float32 m_timeStep;

		//! How strongly to correct velocity.
		int32 m_velocityIterations;

		//! How strongly to correct position.
		int32 m_positionIterations;
	};
}