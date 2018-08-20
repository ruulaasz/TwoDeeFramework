#include "Player.h"

Player::Player()
{
	m_posX = 0;
	m_posY = 0;
	m_texture = nullptr;
	m_enable = true;
}

Player::~Player()
{

}

void Player::init()
{
	m_texture = reinterpret_cast<TDF::Texture*>(TDF::ResourceManager::GetInstance().load("Untitled", TDF::RT_TEXTURE));
}

void Player::render()
{
	if (m_enable)
	{
		m_texture->render(m_posX, m_posY);
	}
}

void Player::destroy()
{
	m_enable = false;
	m_texture->deleteReference();
}
