#include "Level_0.h"
#include "Knight.h"

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

	m_player->enterScene("Level0");
	m_player->m_dynamicBody.setPosition(TDF::Vector2D(300, 500));
}

void Level_0::onExit()
{
	TDF::Scene::onExit();

	String name = "Player_info";
	name = name + " visible=false";
	TwDefine(name.c_str());

	m_world.m_physics->destroyBody(&m_player->m_dynamicBody);
}

void Level_0::update(float _deltaTime)
{
	TDF::Scene::update(_deltaTime);
}

void Level_0::render()
{
	TDF::Scene::render();
}

void Level_0::init()
{
	//creamos mundo fisico
	TDF::Box2DManager::GetInstance().m_allWorlds["Level0"] = TDF::Box2DManager::GetInstance().createWorld("Level0", TDF::Vector2D(0,18));
	m_world.m_physics = TDF::Box2DManager::GetInstance().m_allWorlds["Level0"];

	TDF::Scene::init();
	m_world.addActor(m_player);

	m_backgroundMusic = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Music>("music\\Dirtmouth.wav");

	//floor1
	std::string s = "Level0";
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