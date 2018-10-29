#include "Scene.h"
#include "AudioManager.h"
#include "CameraManager.h"
#include "RenderManager.h"

namespace TDF
{
	Scene::Scene()
	{
		for (size_t i = 0; i < BACKGROUND_TEXTURES; i++)
		{
			m_background[i].m_texture = nullptr;
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
			m_backgroundMusic->playFadeIn(500);
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

		CameraManager::GetInstance().checkWorld(&m_world);
	}

	void Scene::render()
	{
		m_world.render();
	}

	void Scene::init()
	{
		m_world.init();
	}
}