#pragma once

#include "Box2DManager.h"
#include <vector>
#include "Actor.h"

namespace TDF
{
	class World
	{
	public:
		World();
		~World();

		b2World* m_physicsWorld;

		std::vector<Actor*> m_allActors;

		float32 m_timeStep;      //the length of time passed to simulate (seconds)
		int32 m_velocityIterations;   //how strongly to correct velocity
		int32 m_positionIterations;   //how strongly to correct position

		void update(float _deltaTime);
		void render();
		void init();
	};
}