#include "Level_1.h"

Level_1::Level_1()
{

}

Level_1::~Level_1()
{

}

void Level_1::onEnter()
{
	TDF::Scene::onEnter();

	String name = "Player_info";
	name = name + " visible=true";
	TwDefine(name.c_str());
}

void Level_1::onExit()
{
	TDF::Scene::onExit();
}

void Level_1::update(float _deltaTime)
{
	TDF::Scene::update(_deltaTime);
}

void Level_1::render()
{
	TDF::Scene::render();
}

void Level_1::init(TDF::PhysicsWorld * _physicWorld)
{
	m_world.addActor(&m_player);
	m_world.addActor(&m_platform);

	TDF::Scene::init(_physicWorld);

	TDF::InputManager::GetInstance().subscribe(TDF::KEYBOARD_INPUT, m_player.m_id);
	TDF::InputManager::GetInstance().subscribe(TDF::CONTROLLER_INPUT, m_player.m_id);

	m_world.m_physics->m_world->SetContactListener(&m_player.m_contactListener);

	m_backgroundMusic = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Music>("music\\Dirtmouth.wav");

	m_backgroundMusic.get()->play();

	std::string s = "moon";
	SDL_Rect r = SDL_Rect{ 900,800,100,100 };
	int c = TDF::CI_PLATFORM;

	m_platform.init(s, r, c);
}