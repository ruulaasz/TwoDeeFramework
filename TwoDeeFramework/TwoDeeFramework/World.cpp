#include "World.h"
#include "SceneManager.h"
#include "Box2DManager.h"

namespace TDF
{
	World::World()
	{
		m_physics = nullptr;
	}

	World::~World()
	{

	}

	void World::update(float _deltaTime)
	{
		if (m_physics)
		{
			m_physics->update();
		}

		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			m_allActors.at(i)->update(_deltaTime);
		}
	}

	void World::render()
	{
		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			if (m_allActors.at(i)->m_rendereable)
			{
				m_allActors.at(i)->render();
			}
		}

		if (m_physics)
		{
			//m_physics->render();
		}
	}

	void World::init()
	{
		if(!m_physics)
		{
			m_physics = Box2DManager::GetInstance().getWorld("earth");
		}

		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			m_allActors.at(i)->init();
		}
	}

	void World::addActor(Actor * _actor)
	{
		m_allActors.push_back(_actor);
	}
}