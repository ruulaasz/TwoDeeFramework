#include "Player.h"
#include "DebugDraw.h"

Player::Player()
{
	m_texture = nullptr;

#ifdef _WIN64

#else
	infoBar = nullptr;
#endif

	m_movementSpeed = 5.0f;
}

Player::~Player()
{

}

void Player::update(float _deltaTime)
{
	_deltaTime;

	b2Vec2 vel = body->GetLinearVelocity();

	switch (moveState)
	{
	case MS_LEFT:  vel.x = -5; break;
	case MS_STOP:  vel.x = 0; break;
	case MS_RIGHT: vel.x = 5; break;
	}

	body->SetLinearVelocity(vel);

	m_position.x = body->GetPosition().x;
	m_position.y = body->GetPosition().y;
}

void Player::init(b2World* _b2World)
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

	//body definition
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;

	//shape definition
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(m_texture->m_width/2 * SCALE_TO_WORLD, m_texture->m_height / 2 * SCALE_TO_WORLD);

	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	//create dynamic body
	myBodyDef.position.Set(200.0f * SCALE_TO_WORLD, 900.0f * SCALE_TO_WORLD);
	body = _b2World->CreateBody(&myBodyDef);
	body->CreateFixture(&myFixtureDef);
	body->SetFixedRotation(true);

	//a static body
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(1000.0f * SCALE_TO_WORLD, 500.0f * SCALE_TO_WORLD);
	b2Body* staticBody = _b2World->CreateBody(&myBodyDef);

	//add four walls to the static body
	polygonShape.SetAsBox(1000.0f * SCALE_TO_WORLD, 20.0f * SCALE_TO_WORLD, b2Vec2(0.0f, 500.0f * SCALE_TO_WORLD), 0.0f);//ground
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(1000.0f * SCALE_TO_WORLD, 20.0f * SCALE_TO_WORLD, b2Vec2(0.0f, -500.0f * SCALE_TO_WORLD), 0.0f);//ceiling
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(20.0f * SCALE_TO_WORLD, 500.0f * SCALE_TO_WORLD, b2Vec2(-1000.0f * SCALE_TO_WORLD, 0.0f), 0.0f);//left wall
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(20.0f * SCALE_TO_WORLD, 500.0f * SCALE_TO_WORLD, b2Vec2(900.0f * SCALE_TO_WORLD, 0.0f), 0.0f);//right wall
	staticBody->CreateFixture(&myFixtureDef);

	moveState = MS_STOP;
}

void Player::render(float _angle)
{
	int renderPosx = m_position.x * SCALE_TO_RENDER - m_texture->m_width / 2;
	int renderPosY = m_position.y * SCALE_TO_RENDER - m_texture->m_height / 2;
	float renderAngle = _angle * 57.2958f - 90.0f;

	TDF::RenderManager::GetInstance().renderTexture(m_texture, renderPosx,renderPosY, renderAngle);
}