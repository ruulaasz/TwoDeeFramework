#include "CameraManager.h"
#include "World.h"
#include "RenderManager.h"

namespace TDF
{
	CameraManager::CameraManager()
	{
		m_camera.m_areaBox.m_width = SDL_Manager::GetInstance().m_windowWidth;
		m_camera.m_areaBox.m_height = SDL_Manager::GetInstance().m_windowHeight;
	}

	CameraManager::~CameraManager()
	{

	}

	void CameraManager::checkWorld(World * _world)
	{
		m_actorsOnScreen = 0;

		for (size_t i = 0; i < _world->m_allActors.size(); i++)
		{
			if (checkCollision(_world->m_allActors.at(i)))
			{
				_world->m_allActors.at(i)->m_screenPosition = _world->m_allActors.at(i)->m_worldPosition - m_camera.m_areaBox.m_position;
				_world->m_allActors.at(i)->m_rendereable = true;
				++m_actorsOnScreen;
			}
			else
			{
				_world->m_allActors.at(i)->m_rendereable = false;
			}
		}
	}

	bool CameraManager::checkCollision(Actor * _actor)
	{
		if (m_camera.m_areaBox.m_position.x + m_camera.m_areaBox.m_width >= _actor->m_boundingBox.m_position.x &&		// r1 right edge past r2 left
			m_camera.m_areaBox.m_position.x <= _actor->m_boundingBox.m_position.x + _actor->m_boundingBox.m_width &&   // r1 left edge past r2 right
			m_camera.m_areaBox.m_position.y + m_camera.m_areaBox.m_height >= _actor->m_boundingBox.m_position.y &&    // r1 top edge past r2 bottom
			m_camera.m_areaBox.m_position.y <= _actor->m_boundingBox.m_position.y + _actor->m_boundingBox.m_height)	 // r1 bottom edge past r2 top
		{    
			return true;
		}

		return false;
	}

	void CameraManager::renderCamera()
	{
		//RenderManager::GetInstance().renderBox(m_camera.m_areaBox);
	}
}