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

void Level_0::init()
{
	TDF::Scene::init();

	m_backgroundMusic = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Music>("..\\resources\\music\\Dirtmouth.wav");
}