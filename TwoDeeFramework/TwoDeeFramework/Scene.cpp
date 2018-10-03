#include "Scene.h"
#include "AudioManager.h"

namespace TDF
{
	Scene::Scene()
	{
		for (size_t i = 0; i < BACKGROUND_TEXTURES; i++)
		{
			m_background[i] = nullptr;
		}

		m_backgroundMusic = nullptr;
	}

	Scene::~Scene()
	{

	}

	void Scene::onEnter()
	{
		if (m_backgroundMusic)
		{
			m_backgroundMusic->playFadeIn(1000);
		}
	}

	void Scene::onExit()
	{
		if (m_backgroundMusic)
		{
			AudioManager::GetInstance().stopMusicFadeOut(500);
		}
	}

	void Scene::update(float _deltaTime)
	{
		m_world.update(_deltaTime);
	}

	void Scene::render()
	{
		m_world.render();
	}

	void Scene::init(String _worldName)
	{
		m_world.init(_worldName);
	}
}