#include "PhysicsWorld.h"
#include "DynamicBody.h"
#include "StaticBody.h"

namespace TDF
{
	PhysicsWorld::PhysicsWorld()
	{
		m_timeStep = 1 / 60.0f;
		m_velocityIterations = 8;
		m_positionIterations = 3;

		m_world = nullptr;
	}

	PhysicsWorld::PhysicsWorld(b2World * _world)
	{
		m_timeStep = 1 / 60.0f;
		m_velocityIterations = 8;
		m_positionIterations = 3;

		m_world = _world;
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

	void PhysicsWorld::destroyBody(DynamicBody* _body)
	{
		m_world->DestroyBody(_body->m_body);
	}

	void PhysicsWorld::destroyBody(StaticBody* _body)
	{
		m_world->DestroyBody(_body->m_body);
	}

	b2Body* PhysicsWorld::createBody(const b2BodyDef * _def)
	{
		return m_world->CreateBody(_def);
	}
}