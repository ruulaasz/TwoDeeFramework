#include "Player.h"

Player::Player()
{
	m_texture = nullptr;
}

Player::~Player()
{

}

void Player::update(float _deltaTime)
{
	_deltaTime;

	m_position += m_velocity;

	m_mainCB.m_position = m_position;
	m_mainCB.m_velocity= m_velocity;
}

void Player::init()
{
	m_texture = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("..\\resources\\textures\\Untitled.png");
	m_mainCB = TDF::AABB(TDF::Vector2D(m_position), m_texture->m_width, m_texture->m_height);
}

void Player::render(float _angle)
{
	TDF::RenderManager::GetInstance().renderTexture(m_texture, 
												    static_cast<int>(m_position.x), 
												    static_cast<int>(m_position.y), 
												    static_cast<float>((_angle * 57.2958)-90));
	
	m_mainCB.render();
}

void Player::destroy()
{
	
}