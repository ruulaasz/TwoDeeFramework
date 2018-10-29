#include "LevelEvo.h"

LevelEvo::LevelEvo()
{
	m_player = nullptr;
}

LevelEvo::~LevelEvo()
{

}

void LevelEvo::onEnter()
{
	TDF::Scene::onEnter();

	String name = "Cube_info";
	name = name + " visible=true";
	TwDefine(name.c_str());

	m_player->enterScene("LevelEvo");
	m_player->m_dynamicBody.setPosition(TDF::Vector2D(300, 500));
}

void LevelEvo::onExit()
{
	TDF::Scene::onExit();

	String name = "Cube_info";
	name = name + " visible=false";
	TwDefine(name.c_str());

	m_world.m_physics->destroyBody(&m_player->m_dynamicBody);
}

void LevelEvo::update(float _deltaTime)
{
	TDF::Scene::update(_deltaTime);
}

void LevelEvo::render()
{
	TDF::Scene::render();
}

void LevelEvo::init()
{
	//creamos mundo fisico
	TDF::Box2DManager::GetInstance().m_allWorlds["LevelEvo"] = TDF::Box2DManager::GetInstance().createWorld("LevelEvo", TDF::Vector2D(0, 0));
	m_world.m_physics = TDF::Box2DManager::GetInstance().m_allWorlds["LevelEvo"];

	TDF::Scene::init();
	

	m_backgroundMusic = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Music>("music\\Dirtmouth.wav");

	m_background[0].m_texture = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("textures\\levelEvo_background.jpg");
	m_background[0].init(TDF::Vector2D(0, 0), 
		TDF::Vector2D(	TDF::RenderManager::GetInstance().m_renderTargets[TDF::GBUFFER].get()->m_width, 
						TDF::RenderManager::GetInstance().m_renderTargets[TDF::GBUFFER].get()->m_height));

	m_world.addActor(&m_background[0]);

	m_world.addActor(m_player);
	m_world.addActor(m_player->m_tail);
	m_world.addActor(m_player->m_jaws);
	m_world.addActor(m_player->m_fin);

	//floor
	std::string s = "LevelEvo";
	SDL_Rect r = SDL_Rect{ 2000, 2000, 2000, 100 };
	int c = TDF::CI_PLATFORM;
	TDF::Platform* p = new TDF::Platform();
	p->init(s, r, c);
	m_world.addActor(p);

	//ceiling
	r = SDL_Rect{ 2000, 0, 1925, 150 };
	c = 0;
	p = new TDF::Platform();
	p->init(s, r, c);
	m_world.addActor(p);

	//left wall
	r = SDL_Rect{ 25, 2000, 100, 2000 };
	c = 0;
	p = new TDF::Platform();
	p->init(s, r, c);
	m_world.addActor(p);

	//right wall
	r = SDL_Rect{ 3900, 2000, 100, 2000 };
	c = 0;
	p = new TDF::Platform();
	p->init(s, r, c);
	m_world.addActor(p);

	r = SDL_Rect{ 1900, 1800, 700, 250 };
	c = 0;
	p = new TDF::Platform();
	p->init(s, r, c);
	m_world.addActor(p);

	p->m_texture = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("textures\\platform_default.png");

	r = SDL_Rect{ 1375, 1300, 175, 250 };
	c = 0;
	p = new TDF::Platform();
	p->init(s, r, c);
	m_world.addActor(p);

	p->m_texture = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("textures\\platform_default.png");

	r = SDL_Rect{ 2250, 1400, 350, 150 };
	c = 0;
	p = new TDF::Platform();
	p->init(s, r, c);
	m_world.addActor(p);

	p->m_texture = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("textures\\platform_default.png");

	r = SDL_Rect{ 2300, 950, 250, 300 };
	c = 0;
	p = new TDF::Platform();
	p->init(s, r, c);
	m_world.addActor(p);

	p->m_texture = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("textures\\platform_default.png");
}