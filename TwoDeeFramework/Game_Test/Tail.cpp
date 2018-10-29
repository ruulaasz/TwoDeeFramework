#include "Tail.h"

Tail::Tail()
{
	m_offset.x = -75;
	m_offset.y = 0;

	m_speedMod = 1;
}

Tail::~Tail()
{

}

void Tail::render()
{
	TDF::RenderManager::GetInstance().renderTexture(m_texture, m_screenPosition.x, m_screenPosition.y);

	TDF::AABB renderBox = m_boundingBox;
	renderBox.m_position.x = m_screenPosition.x;
	renderBox.m_position.y = m_screenPosition.y;

	TDF::RenderManager::GetInstance().renderBox(renderBox);
}

void Tail::init()
{
	m_texture = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("textures\\tail.png");

	m_boundingBox.m_width = m_texture->m_width;
	m_boundingBox.m_height = m_texture->m_height;
}

void Tail::update(float _deltaTime)
{
	_deltaTime;

	m_boundingBox.m_position.x = m_worldPosition.x - m_texture->m_width / 2.0f;
	m_boundingBox.m_position.y = m_worldPosition.y - m_texture->m_height / 2.0f;
}