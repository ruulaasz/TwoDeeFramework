#include "Jaws.h"

Jaws::Jaws()
{
	m_damageMod = 1;
}

Jaws::~Jaws()
{

}

void Jaws::render()
{
	if (m_flipped)
	{
		TDF::RenderManager::GetInstance().renderAnimation(m_jawsAnim, m_screenPosition.x + 5, m_screenPosition.y, 0, 4, nullptr, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TDF::RenderManager::GetInstance().renderAnimation(m_jawsAnim, m_screenPosition.x, m_screenPosition.y, 0, 4, nullptr, SDL_FLIP_NONE);
	}

	if (TDF::SystemManager::GetInstance().m_renderDebug)
	{
		TDF::AABB renderBox = m_boundingBox;
		renderBox.m_position.x = m_screenPosition.x;
		renderBox.m_position.y = m_screenPosition.y;

		TDF::RenderManager::GetInstance().renderBox(renderBox);
	}
}

void Jaws::init()
{
	m_jawsAnim = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Animation>("animations\\jaws.xml");

	m_boundingBox.m_width = m_jawsAnim->getCurrentSprite().m_dimentions.x * 4;
	m_boundingBox.m_height = m_jawsAnim->getCurrentSprite().m_dimentions.y * 4;
}

void Jaws::update(float _deltaTime)
{
	_deltaTime;

	m_jawsAnim->update();

	m_boundingBox.m_position.x = m_worldPosition.x - m_jawsAnim->getCurrentSprite().m_dimentions.x * 4;
	m_boundingBox.m_position.y = m_worldPosition.y - m_jawsAnim->getCurrentSprite().m_dimentions.y * 4;
}