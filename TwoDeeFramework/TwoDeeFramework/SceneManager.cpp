#include "SceneManager.h"

namespace TDF
{
	SceneManager::SceneManager()
	{
		m_activeScene = nullptr;
		m_currentID = 1;
	}

	SceneManager::~SceneManager()
	{

	}

	Actor * TDF::SceneManager::getActor(int _id)
	{
		if (m_activeScene)
		{
			for (size_t i = 0; i < m_activeScene->m_world.m_allActors.size(); i++)
			{
				if (m_activeScene->m_world.m_allActors.at(i)->m_id == _id)
				{
					return m_activeScene->m_world.m_allActors.at(i);
				}
			}
		}

		return nullptr;
	}

	void TDF::SceneManager::setActiveScene(Scene * _scene)
	{
		m_activeScene = _scene;
	}

	int TDF::SceneManager::getID()
	{
		m_currentID++;
		return m_currentID - 1;
	}
}