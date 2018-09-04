#include "Player.h"

Player::Player()
{
	m_texture = nullptr;
	m_enable = true;

#ifdef _WIN64

#else
	m_steerBar = nullptr;
	*vel = 0;
	*des = 0;
	*steer = 0;
#endif
}

Player::~Player()
{

}

void Player::update(float _deltaTime)
{
	_deltaTime;

#ifdef _WIN64

#else
	/*vel[0] = m_body.m_velocity.x;
	vel[1] = m_body.m_velocity.y;
	vel[2] = 0.0f;

	des[0] = m_body.m_desiredVelocity.x;
	des[1] = m_body.m_desiredVelocity.y;
	des[2] = 0.0f;

	steer[0] = m_body.m_finalForce.x;
	steer[1] = m_body.m_finalForce.y;
	steer[2] = 0.0f;*/
#endif
}

void Player::init()
{
	m_texture = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("..\\resources\\textures\\Untitled.png");
}

void Player::render(float _angle)
{
	if (m_enable)
	{
		TDF::RenderManager::GetInstance().renderTexture(m_texture, 
													    static_cast<int>(m_position.x - m_texture->m_width / 2), 
													    static_cast<int>(m_position.y - m_texture->m_height / 2), 
													    static_cast<float>((_angle * 57.2958)-90));

		/*SDL_SetRenderDrawColor(TDF::SDL_Manager::GetInstance().m_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		TDF::SDL_Manager::GetInstance().renderCircle(m_target->m_arrivalRadius, static_cast<int>(m_target->m_position.x), static_cast<int>(m_target->m_position.y));
		TDF::SDL_Manager::GetInstance().renderCircle(m_body.m_stopRadius, static_cast<int>(m_target->m_position.x), static_cast<int>(m_target->m_position.y));
		TDF::SDL_Manager::GetInstance().renderCircle(m_body.m_stopRadius, static_cast<int>(m_body.m_futurePosition.x), static_cast<int>(m_body.m_futurePosition.y));*/
	}
}

void Player::destroy()
{
	m_enable = false;
}
