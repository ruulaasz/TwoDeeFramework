#include "Level_1.h"
#include "Knight.h"

Level_1::Level_1()
{
	m_player = nullptr;
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

	m_player->enterScene("Level1");
	m_player->m_dynamicBody.setPosition(TDF::Vector2D(900, 500));
}

void Level_1::onExit()
{
	TDF::Scene::onExit();

	String name = "Player_info";
	name = name + " visible=false";
	TwDefine(name.c_str());

	m_world.m_physics->destroyBody(&m_player->m_dynamicBody);
}

void Level_1::update(float _deltaTime)
{
	TDF::Scene::update(_deltaTime);
}

void Level_1::render()
{
	TDF::Scene::render();
}

void Level_1::init()
{
	//creamos mundo fisico
	TDF::Box2DManager::GetInstance().m_allWorlds["Level1"] = TDF::Box2DManager::GetInstance().createWorld("Level1", TDF::Vector2D(0, 25));
	m_world.m_physics = TDF::Box2DManager::GetInstance().m_allWorlds["Level1"];

	TDF::Scene::init();
	m_world.addActor(m_player);

	m_backgroundMusic = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Music>("music\\green_path_atmos_loop.wav");

	//floor1
	std::string s = "Level1";
	SDL_Rect r = SDL_Rect{ 960, 950, 300, 50 };
	int c = TDF::CI_PLATFORM;
	TDF::Platform* p = new TDF::Platform();

	p->m_texture = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("textures\\platform_default.jpg");

	p->init(s, r, c);
	m_world.addActor(p);
}