#include "World.h"

namespace TDF
{
	World::World()
	{
		m_timeStep = 1 / 60.0f;
		m_velocityIterations = 8;
		m_positionIterations = 3;

		m_physicsWorld = nullptr;
	}

	World::~World()
	{

	}

	void World::update(float _deltaTime)
	{
		m_physicsWorld->Step(m_timeStep, m_velocityIterations, m_positionIterations);

		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			m_allActors.at(i)->update(_deltaTime);
		}
	}

	void World::render()
	{
		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			m_allActors.at(i)->render();
		}

		m_physicsWorld->DrawDebugData();
	}

	void World::init()
	{
		m_physicsWorld = Box2DManager::GetInstance().m_allWorlds["earth"];
	}

	void World::addActor(Actor * _actor)
	{
		m_allActors.push_back(_actor);
	}
}