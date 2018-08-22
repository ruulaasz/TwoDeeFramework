#include "Player.h"

Player::Player()
{
	m_texture = nullptr;
	m_enable = true;
	m_target = new SB::Target();
	m_maxVelocity = 5;
}

Player::~Player()
{

}

void Player::update(float _deltaTime)
{
	m_target->m_position.x = TDF::SDL_Manager::GetInstance().m_mousePosX;
	m_target->m_position.y = TDF::SDL_Manager::GetInstance().m_mousePosY;

	m_body.update(_deltaTime);

	m_position = m_body.m_position;

	vel[0] = m_body.m_velocity.x;
	vel[1] = m_body.m_velocity.y;
	vel[2] = 0.0f;

	des[0] = m_body.m_desiredVelocity.x;
	des[1] = m_body.m_desiredVelocity.y;
	des[2] = 0.0f;

	steer[0] = m_body.m_finalForce.x;
	steer[1] = m_body.m_finalForce.y;
	steer[2] = 0.0f;
}

void Player::init()
{
	m_texture = reinterpret_cast<TDF::Texture*>(TDF::ResourceManager::GetInstance().load("Untitled", TDF::RT_TEXTURE));

	m_position.x = TDF::SDL_Manager::GetInstance().m_windowWidth / 2;
	m_position.y = TDF::SDL_Manager::GetInstance().m_windowHeight / 2;

	m_body.m_position = m_position;

	m_body.setTarget(m_target);
	m_target->m_arrivalRadius = 100;
	m_target->m_stopRadius = 10;

	m_body.m_type = SB::BT_ARRIVALSEEK;
	m_body.m_maxVelocity = m_maxVelocity;

	TDF::AntTweakBarInfo info;
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
}

void Player::render()
{
	if (m_enable)
	{
		m_texture->render(m_position.x - m_texture->getWidth()/2 , m_position.y - m_texture->getHeight()/2);
		SDL_SetRenderDrawColor(TDF::SDL_Manager::GetInstance().m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		TDF::SDL_Manager::GetInstance().renderCircle(m_target->m_arrivalRadius, m_target->m_position.x, m_target->m_position.y);
		TDF::SDL_Manager::GetInstance().renderCircle(m_target->m_stopRadius, m_target->m_position.x, m_target->m_position.y);
	}
}

void Player::destroy()
{
	m_enable = false;
	m_texture->deleteReference();
}
