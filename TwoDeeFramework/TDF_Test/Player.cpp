#include "Player.h"

Player::Player()
{
	m_texture = nullptr;

#ifdef _WIN64

#else
	infoBar = nullptr;
#endif

	m_movementSpeed = 2.2f;
}

Player::~Player()
{

}

void Player::update(float _deltaTime)
{
	_deltaTime;

	m_position += m_velocity;
}

void Player::init()
{
	m_texture = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("..\\resources\\textures\\Untitled.png");

#ifdef _WIN64

#else
	TDF::AntTweakBarInfo info;
	info.size = " size='200 300' ";
	info.position = " position='0 500' ";
	infoBar = TDF::AnttweakbarManager::GetInstance().createCustomBar(TEXT("Player_info"), info);
	TwAddVarRO(infoBar, TEXT("position x:"), TW_TYPE_FLOAT, &m_position.x, TEXT(" label='position x:' "));
	TwAddVarRO(infoBar, TEXT("position y:"), TW_TYPE_FLOAT, &m_position.y, TEXT(" label='position y:' "));
#endif
}

void Player::render(float _angle)
{
	TDF::RenderManager::GetInstance().renderTexture(m_texture, 
												    static_cast<int>(m_position.x), 
												    static_cast<int>(m_position.y), 
												    static_cast<float>((_angle * 57.2958)-90));
}

void Player::destroy()
{
	
}