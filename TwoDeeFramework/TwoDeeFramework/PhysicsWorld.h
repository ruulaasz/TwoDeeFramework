#pragma once

#include "StdHeaders.h"
#include <Box2D.h>

namespace TDF
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		PhysicsWorld(b2World* _world);
		~PhysicsWorld();

		void update();
		void render();

		//! The physiscs of the world.
		b2World* m_world;
		String m_name;

	private:
		//! The length of time passed to simulate (seconds).
		float32 m_timeStep;

		//! How strongly to correct velocity.
		int32 m_velocityIterations;

		//! How strongly to correct position.
		int32 m_positionIterations;
	};
}