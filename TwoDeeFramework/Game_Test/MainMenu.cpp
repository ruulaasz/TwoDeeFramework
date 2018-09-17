#include "MainMenu.h"

MainMenu::MainMenu()
{
	for (size_t i = 0; i < BACKGROUND_TEXTURES; i++)
	{
		m_background[i] = nullptr;
	}
}

MainMenu::~MainMenu()
{

}

void MainMenu::onEnter()
{
	m_lightAlpha = 240;
	m_alphaTarget = 0;

	//background
	m_background[0] = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("..\\resources\\textures\\abyss_wall.png");
	m_background[1] = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("..\\resources\\textures\\mainmenu_background_0.png");
	m_background[2] = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("..\\resources\\textures\\lighthouse_light.png");
	m_background[3] = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("..\\resources\\textures\\bone_bench_lit.png");
	m_background[4] = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("..\\resources\\textures\\title.png");
	
	//new game button
	m_newGameB.init();
	m_newGameB.m_dimentions.y = 50;
	m_newGameB.m_dimentions.x = 200;
	m_newGameB.m_position.x = 870;
	m_newGameB.m_position.y = 600;

	//new game button text
	m_newGameB.m_text = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Text>("..\\resources\\fonts\\Perpetua.ttf");
	m_newGameB.m_string = "New Game";
	m_newGameB.m_text->resizeText(48);
	m_newGameB.m_text->m_textColor = TDF::Color(255, 255, 255);

	//new game button
	m_quitGameB.init();
	m_quitGameB.m_dimentions.y = 50;
	m_quitGameB.m_dimentions.x = 100;
	m_quitGameB.m_position.x = 920;
	m_quitGameB.m_position.y = 700;

	//quit game button text
	m_quitGameB.m_text = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Text>("..\\resources\\fonts\\Perpetua.ttf");
	m_quitGameB.m_string = "Quit";
	m_quitGameB.m_text->resizeText(48);
	m_quitGameB.m_text->m_textColor = TDF::Color(255, 255, 255);

	//quit world and add actor
	m_world.init();
	m_world.addActor(&m_newGameB);
	m_world.addActor(&m_quitGameB);
}

void MainMenu::onExit()
{

}

float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

void MainMenu::update(float _deltaTime)
{
	m_world.update(_deltaTime);

	//light effect
	m_background[2]->setAlpha(m_lightAlpha);
	m_background[3]->setAlpha(m_lightAlpha);

	m_lightAlpha = lerp(m_lightAlpha, m_alphaTarget, _deltaTime / 2);

	if (m_lightAlpha <= 20)
	{
		m_lightAlpha = 20;
		m_alphaTarget = 255;
	}

	if (m_lightAlpha >= 240)
	{
		m_lightAlpha = 240;
		m_alphaTarget = 0;
	}

	//option selection
	if (m_newGameB.m_pressed)
	{
		reset();
	}

	if (m_quitGameB.m_pressed)
	{
		SDL_Event e;
		e.type = SDL_QUIT;
		TDF::InputManager::GetInstance().pushEvent(e);
	}
}

void MainMenu::render()
{
	//bench
	TDF::RenderManager::GetInstance().renderTexture(m_background[3], 850, 850);
	
	//light
	TDF::RenderManager::GetInstance().renderTexture(m_background[2], 0, 500);

	//title
	TDF::RenderManager::GetInstance().renderTexture(m_background[4], 560, 150);

	//background
	TDF::RenderManager::GetInstance().renderTexture(m_background[1], 175, 0);

	//pillars
	TDF::RenderManager::GetInstance().renderTexture(m_background[0], -380, 0);
	TDF::RenderManager::GetInstance().renderTexture(m_background[0], 1720, 0);

	//actores de la escena en este caso botones
	m_world.render();
}

void MainMenu::reset()
{
	//reset light effect
	m_lightAlpha = 240;
	m_alphaTarget = 0;

	m_newGameB.m_pressed = false;
	m_quitGameB.m_pressed = false;
}