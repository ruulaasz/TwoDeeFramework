#include "World.h"
#include "SceneManager.h"

namespace TDF
{
	World::World()
	{
		
	}

	World::~World()
	{

	}

	void World::update(float _deltaTime)
	{
		m_physics.update();

		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			m_allActors.at(i)->update(_deltaTime);
		}
	}

	void World::render()
	{
		m_physics.render();

		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			m_allActors.at(i)->render();
		}
	}

	void World::init(String _worldName)
	{
		m_physics.init(_worldName);

		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			m_allActors.at(i)->init();
		}
	}

	void World::addActor(Actor * _actor)
	{
		_actor->m_id = SceneManager::GetInstance().getID();
		m_allActors.push_back(_actor);
	}
}