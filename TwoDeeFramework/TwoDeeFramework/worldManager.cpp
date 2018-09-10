#include "WorldManager.h"

namespace TDF
{
	WorldManager::WorldManager()
	{
		m_activeWorld = nullptr;
	}

	WorldManager::~WorldManager()
	{

	}

	Actor * WorldManager::getActor(int _id)
	{
		for (size_t i = 0; i < m_activeWorld->m_allActors.size(); i++)
		{
			if (m_activeWorld->m_allActors.at(i)->m_id == _id)
			{
				return m_activeWorld->m_allActors.at(i);
			}
		}

		return nullptr;
	}

	void WorldManager::setActiveWorld(World * _world)
	{
		m_activeWorld = _world;
	}
}