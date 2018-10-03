#include "Level_0.h"
#include "Platform.h"

Level_0::Level_0()
{

}

Level_0::~Level_0()
{

}

void Level_0::onEnter()
{
	TDF::Scene::onEnter();

	String name = "Player_info";
	name = name + " visible=true";
	TwDefine(name.c_str());
}

void Level_0::onExit()
{
	TDF::Scene::onExit();
}

void Level_0::update(float _deltaTime)
{
	TDF::Scene::update(_deltaTime);
}

void Level_0::render()
{
	TDF::Scene::render();
}

void Level_0::init(String _worldName)
{
	m_world.addActor(&m_player);
	
	TDF::Scene::init(_worldName);

	TDF::InputManager::GetInstance().subscribe(TDF::KEYBOARD_INPUT, m_player.m_id);
	TDF::InputManager::GetInstance().subscribe(TDF::CONTROLLER_INPUT, m_player.m_id);

	m_backgroundMusic = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Music>("..\\resources\\music\\Dirtmouth.wav");

	m_backgroundMusic.get()->play();

	//PLATFORMS
	b2BodyDef myBodyDef;
	b2Body* staticBody;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(1000.0f * SCALE_TO_PHYSICS, 500.0f * SCALE_TO_PHYSICS);
	staticBody = m_player.m_psysicsWorld->CreateBody(&myBodyDef);

	b2PolygonShape polygonShape;

	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;
	myFixtureDef.friction = 0.0f;

	polygonShape.SetAsBox(4000 * SCALE_TO_PHYSICS, 50 * SCALE_TO_PHYSICS, b2Vec2(3000 * SCALE_TO_PHYSICS, -500 * SCALE_TO_PHYSICS), 0.0f);//ceiling
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(50.0f * SCALE_TO_PHYSICS, 500.0f * SCALE_TO_PHYSICS, b2Vec2(-1000.0f * SCALE_TO_PHYSICS, 0.0f), 0.0f);//left wall
	staticBody->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(50.0f * SCALE_TO_PHYSICS, 1200.0f * SCALE_TO_PHYSICS, b2Vec2(4000.0f * SCALE_TO_PHYSICS, 650.0f * SCALE_TO_PHYSICS), 0.0f);//right wall
	staticBody->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(50.0f * SCALE_TO_PHYSICS, 1000.0f * SCALE_TO_PHYSICS, b2Vec2(2900.0f * SCALE_TO_PHYSICS, 900.0f * SCALE_TO_PHYSICS), 0.0f);//right wall
	staticBody->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(50.0f * SCALE_TO_PHYSICS, 500.0f * SCALE_TO_PHYSICS, b2Vec2(1100.0f * SCALE_TO_PHYSICS, 3000.0f * SCALE_TO_PHYSICS), 0.0f);//right wall
	staticBody->CreateFixture(&myFixtureDef);

	//a static body
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(1000.0f * SCALE_TO_PHYSICS, 500.0f * SCALE_TO_PHYSICS);
	b2Body* platformBody = m_player.m_psysicsWorld->CreateBody(&myBodyDef);

	Platform* platform = new Platform();
	platform->m_collisionID = CI_PLATFORM;

	platformBody->SetUserData(platform);

	polygonShape.SetAsBox(2000 * SCALE_TO_PHYSICS, 50 * SCALE_TO_PHYSICS, b2Vec2(900 * SCALE_TO_PHYSICS, 500.0f * SCALE_TO_PHYSICS), 0.0f);//ground
	platformBody->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(4000 * SCALE_TO_PHYSICS, 50 * SCALE_TO_PHYSICS, b2Vec2(2800 * SCALE_TO_PHYSICS, 3500.0f * SCALE_TO_PHYSICS), 0.0f);//ground
	platformBody->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(800 * SCALE_TO_PHYSICS, 50 * SCALE_TO_PHYSICS, b2Vec2(6700 * SCALE_TO_PHYSICS, 500.0f * SCALE_TO_PHYSICS), 0.0f);//ground
	platformBody->CreateFixture(&myFixtureDef);

	//platforms

	polygonShape.SetAsBox(100.0f * SCALE_TO_PHYSICS, 90.0f * SCALE_TO_PHYSICS, b2Vec2(500.0f  * SCALE_TO_PHYSICS, 350.0f * SCALE_TO_PHYSICS), 0.0f);//platform
	staticBody->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(90.0f * SCALE_TO_PHYSICS, 20.0f * SCALE_TO_PHYSICS, b2Vec2(500.0f * SCALE_TO_PHYSICS, 270.0f * SCALE_TO_PHYSICS), 0.0f);//platform/recharge jump
	platformBody->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(200.0f * SCALE_TO_PHYSICS, 50.0f * SCALE_TO_PHYSICS, b2Vec2(1700.0f  * SCALE_TO_PHYSICS, 175.0f * SCALE_TO_PHYSICS), 0.0f);//platform
	staticBody->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(190.0f * SCALE_TO_PHYSICS, 20.0f * SCALE_TO_PHYSICS, b2Vec2(1700.0f * SCALE_TO_PHYSICS, 135.0f * SCALE_TO_PHYSICS), 0.0f);//platform/recharge jump
	platformBody->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(200.0f * SCALE_TO_PHYSICS, 50.0f * SCALE_TO_PHYSICS, b2Vec2(2000.0f  * SCALE_TO_PHYSICS, 175.0f * SCALE_TO_PHYSICS), 0.0f);//platform
	staticBody->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(190.0f * SCALE_TO_PHYSICS, 20.0f * SCALE_TO_PHYSICS, b2Vec2(2000.0f * SCALE_TO_PHYSICS, 135.0f * SCALE_TO_PHYSICS), 0.0f);//platform/recharge jump
	platformBody->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(200.0f * SCALE_TO_PHYSICS, 50.0f * SCALE_TO_PHYSICS, b2Vec2(3500.0f  * SCALE_TO_PHYSICS, 1000.0f * SCALE_TO_PHYSICS), 0.0f);//platform
	staticBody->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(190.0f * SCALE_TO_PHYSICS, 20.0f * SCALE_TO_PHYSICS, b2Vec2(3500.0f * SCALE_TO_PHYSICS, 900.0f * SCALE_TO_PHYSICS), 0.0f);//platform/recharge jump
	platformBody->CreateFixture(&myFixtureDef);
}