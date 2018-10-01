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

	Actor * SceneManager::getActor(int _id)
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

	void SceneManager::setActiveScene(string _scene)
	{
		auto it = m_allScenes.find(_scene);

		if (it != m_allScenes.end())
		{
			if (m_activeScene)
			{
				m_activeScene->onExit();
			}

			m_activeScene = it->second;
			m_activeScene->onEnter();
		}
	}

	int SceneManager::getID()
	{
		m_currentID++;
		return m_currentID - 1;
	}
}