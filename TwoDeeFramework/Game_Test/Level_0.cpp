#include "Level_0.h"

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

void Level_0::init(TDF::PhysicsWorld* _physicWorld)
{
	m_world.addActor(&m_player);

	TDF::Scene::init(_physicWorld);

	TDF::InputManager::GetInstance().subscribe(TDF::KEYBOARD_INPUT, m_player.m_id);
	TDF::InputManager::GetInstance().subscribe(TDF::CONTROLLER_INPUT, m_player.m_id);

	m_world.m_physics->m_world->SetContactListener(&m_player.m_contactListener);

	m_backgroundMusic = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Music>("music\\Dirtmouth.wav");

	m_backgroundMusic.get()->play();

	//floor1
	std::string s = "moon";
	SDL_Rect r = SDL_Rect{ 960, 950, 1000, 50 };
	int c = TDF::CI_PLATFORM;
	TDF::Platform* p = new TDF::Platform();

	p->init(s, r, c);
	m_world.addActor(p);

	//bump1
	r = SDL_Rect{ 900, 800, 100, 100 };
	c = 0;
	p = new TDF::Platform();
	p->init(s, r, c);
	m_world.addActor(p);

	//bump1 recharge
	r = SDL_Rect{ 900, 705, 95, 5 };
	c = TDF::CI_PLATFORM;
	p = new TDF::Platform();
	p->init(s, r, c);
	m_world.addActor(p);

	//wall1
	r = SDL_Rect{ 50, 540, 50, 540 };
	c = 0;
	p = new TDF::Platform();
	p->init(s, r, c);
	m_world.addActor(p);
}