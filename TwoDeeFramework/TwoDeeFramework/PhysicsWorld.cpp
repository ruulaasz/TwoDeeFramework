#include "PhysicsWorld.h"

namespace TDF
{
	PhysicsWorld::PhysicsWorld()
	{
		m_timeStep = 1 / 60.0f;
		m_velocityIterations = 8;
		m_positionIterations = 3;

		m_world = nullptr;
	}

	PhysicsWorld::~PhysicsWorld()
	{

	}

	void PhysicsWorld::update()
	{
		m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);
	}

	void PhysicsWorld::render()
	{
		m_world->DrawDebugData();
	}

	void PhysicsWorld::init(String _worldName)
	{
		m_world = Box2DManager::GetInstance().m_allWorlds[_worldName];
	}

	void PhysicsWorld::init(b2World * _world)
	{
		m_world = _world;
	}
}