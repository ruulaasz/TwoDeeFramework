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
	m_texture = reinterpret_cast<TDF::Texture*>(TDF::ResourceManager::GetInstance().load("Untitled", TDF::RT_TEXTURE));

#ifdef _WIN64

#else
	/*TDF::AntTweakBarInfo info;
	info.size = " size='300 400' ";
	info.position = " position='0 300' ";
	info.valuesWidth = " valueswidth=100 ";
	m_steerBar = TDF::AnttweakbarManager::GetInstance().createCustomBar(TEXT("Steering_Info"), info);
	TwAddVarRO(m_steerBar, TEXT("Velocity:"), TW_TYPE_DIR3D, &vel, "");
	TwAddVarRO(m_steerBar, TEXT("Steer Force:"), TW_TYPE_DIR3D, &steer, "");
	TwAddVarRO(m_steerBar, TEXT("Desired:"), TW_TYPE_DIR3D, &des, "");
	TwAddVarRW(m_steerBar, TEXT("SeekScale:"), TW_TYPE_FLOAT, &m_body.m_seekScalar, TEXT("group='Behavior scale' label='SeekScale:' min=0 max=10 step=0.1"));
	TwAddVarRW(m_steerBar, TEXT("FleeScale:"), TW_TYPE_FLOAT, &m_body.m_fleeScalar, TEXT("group='Behavior scale' label='FleeScale:' min=0 max=10 step=0.1"));
	TwAddVarRW(m_steerBar, TEXT("ArrivalScale:"), TW_TYPE_FLOAT, &m_body.m_arrivalScalar, TEXT("group='Behavior scale' label='ArrivalScale:' min=0 max=10 step=0.1"));
	TwAddVarRW(m_steerBar, TEXT("WanderScale:"), TW_TYPE_FLOAT, &m_body.m_wanderScalar, TEXT("group='Behavior scale' label='WanderScale:' min=0 max=10 step=0.1"));*/
#endif
	
}

void Player::render(float _angle)
{
	if (m_enable)
	{
		m_texture->render(static_cast<int>(m_posX - m_texture->getWidth() / 2) , static_cast<int>(m_posY - m_texture->getHeight() / 2), _angle);
		/*SDL_SetRenderDrawColor(TDF::SDL_Manager::GetInstance().m_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		TDF::SDL_Manager::GetInstance().renderCircle(m_target->m_arrivalRadius, static_cast<int>(m_target->m_position.x), static_cast<int>(m_target->m_position.y));
		TDF::SDL_Manager::GetInstance().renderCircle(m_body.m_stopRadius, static_cast<int>(m_target->m_position.x), static_cast<int>(m_target->m_position.y));
		TDF::SDL_Manager::GetInstance().renderCircle(m_body.m_stopRadius, static_cast<int>(m_body.m_futurePosition.x), static_cast<int>(m_body.m_futurePosition.y));*/
	}
}

void Player::destroy()
{
	m_enable = false;
	m_texture->deleteReference();
}
