#include "Player.h"
#include "Platform.h"

Player::Player()
{
	m_texture = nullptr;
	m_nameText = nullptr;

#ifdef _WIN64

#else
	infoBar = nullptr;
#endif

	m_movementSpeed = 5.0f;
	m_jumpSpeed = 10.0f;
	m_angle = 0;

	m_canJump = true;
	m_jumpLimit = 2;
	m_currentJumps = 0;
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
	case MS_LEFT:  vel.x = -m_movementSpeed; break;
	case MS_STOP:  vel.x = 0; break;
	case MS_RIGHT: vel.x = m_movementSpeed; break;
	}

	body->SetLinearVelocity(vel);

	m_velocity.x = vel.x;
	m_velocity.y = vel.y;

	if (m_currentJumps >= m_jumpLimit)
	{
		m_canJump = false;
	}

	m_position.x = body->GetPosition().x;
	m_position.y = body->GetPosition().y;
}

void Player::init()
{
	m_texture = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("..\\resources\\textures\\Untitled.png");
	m_nameText = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Text>("..\\resources\\fonts\\OptimusPrinceps.ttf");

	//m_nameText->setStyle(TTF_STYLE_BOLD);
	//m_nameText->resizeText(48);

#ifdef _WIN64

#else
	TDF::AntTweakBarInfo info;
	info.size = " size='200 300' ";
	info.position = " position='0 500' ";
	infoBar = TDF::AnttweakbarManager::GetInstance().createCustomBar(TEXT("Player_info"), info);
	TwAddVarRO(infoBar, TEXT("position x:"), TW_TYPE_FLOAT, &m_position.x, TEXT(" label='position x:' "));
	TwAddVarRO(infoBar, TEXT("position y:"), TW_TYPE_FLOAT, &m_position.y, TEXT(" label='position y:' "));
	TwAddVarRO(infoBar, TEXT("velocity x:"), TW_TYPE_FLOAT, &m_velocity.x, TEXT(" label='velocity x:' "));
	TwAddVarRO(infoBar, TEXT("velocity y:"), TW_TYPE_FLOAT, &m_velocity.y, TEXT(" label='velocity y:' "));
#endif

	//body definition
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;

	//shape definition
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(m_texture->m_width / 2.0f * SCALE_TO_WORLD, m_texture->m_height / 2.0f * SCALE_TO_WORLD);

	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;
	myFixtureDef.friction = 0.0f;

	//create dynamic body
	myBodyDef.position.Set(900.0f * SCALE_TO_WORLD, 500.0f * SCALE_TO_WORLD);
	body = world->CreateBody(&myBodyDef);
	world->SetContactListener(&m_contactListener);
	body->SetUserData(this);
	body->CreateFixture(&myFixtureDef);
	body->SetFixedRotation(true);

	//a static body
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(1000.0f * SCALE_TO_WORLD, 500.0f * SCALE_TO_WORLD);
	b2Body* staticBody = world->CreateBody(&myBodyDef);

	//add four walls to the static body
	polygonShape.SetAsBox(1000.0f * SCALE_TO_WORLD, 20.0f * SCALE_TO_WORLD, b2Vec2(0.0f, -500.0f * SCALE_TO_WORLD), 0.0f);//ceiling
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(20.0f * SCALE_TO_WORLD, 500.0f * SCALE_TO_WORLD, b2Vec2(-1000.0f * SCALE_TO_WORLD, 0.0f), 0.0f);//left wall
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(20.0f * SCALE_TO_WORLD, 500.0f * SCALE_TO_WORLD, b2Vec2(900.0f * SCALE_TO_WORLD, 0.0f), 0.0f);//right wall
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(100.0f * SCALE_TO_WORLD, 50.0f * SCALE_TO_WORLD, b2Vec2(-100.0f * SCALE_TO_WORLD, 300.0f * SCALE_TO_WORLD), 0.0f);//right wall
	staticBody->CreateFixture(&myFixtureDef);

	//a static body
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(1000.0f * SCALE_TO_WORLD, 500.0f * SCALE_TO_WORLD);
	b2Body* platformBody = world->CreateBody(&myBodyDef);

	Platform* platform = new Platform();
	platform->m_collisionID = CI_PLATFORM;

	platformBody->SetUserData(platform);

	polygonShape.SetAsBox(1000.0f * SCALE_TO_WORLD, 20.0f * SCALE_TO_WORLD, b2Vec2(0.0f, 500.0f * SCALE_TO_WORLD), 0.0f);//ground
	platformBody->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(90.0f * SCALE_TO_WORLD, 20.0f * SCALE_TO_WORLD, b2Vec2(-100.0f * SCALE_TO_WORLD, 270.0f * SCALE_TO_WORLD), 0.0f);//right wall
	platformBody->CreateFixture(&myFixtureDef);

	moveState = MS_STOP;
}

void Player::render()
{
	int renderPosx = static_cast<int>(m_position.x * SCALE_TO_RENDER - m_texture->m_width / 2);
	int renderPosy = static_cast<int>(m_position.y * SCALE_TO_RENDER - m_texture->m_height / 2);
	float renderAngle = m_angle * 57.2958f - 90.0f;

	TDF::RenderManager::GetInstance().renderTexture(m_texture, renderPosx, renderPosy, renderAngle);

	renderPosx -= m_texture->m_width / 2;
	renderPosy -= m_texture->m_height / 2;
	TDF::RenderManager::GetInstance().renderText(m_nameText, "This is a box", renderPosx, renderPosy);
}

void Player::onEnterCollision(int _tag)
{
	if (_tag == CI_PLATFORM)
	{
		m_currentJumps = 0;
		m_canJump = true;
	}
}

void Player::jump()
{
	if (m_canJump)
	{
		b2Vec2 vel = body->GetLinearVelocity();
		vel.y = -m_jumpSpeed;
		body->SetLinearVelocity(vel);
		m_currentJumps++;
	}
}
