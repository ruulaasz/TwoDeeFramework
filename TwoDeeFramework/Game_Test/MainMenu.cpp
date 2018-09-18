#include "MainMenu.h"

MainMenu::MainMenu()
{
	for (size_t i = 0; i < BACKGROUND_TEXTURES; i++)
	{
		m_background[i] = nullptr;
	}

	m_titleTheme = nullptr;
	m_grassAnimation = nullptr;
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
	m_newGameB.m_position.x = 870;
	m_newGameB.m_position.y = 600;

	//new game button text
	m_newGameB.m_text = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Text>("..\\resources\\fonts\\Perpetua.ttf");
	m_newGameB.m_text->resizeText(48);
	m_newGameB.m_text->setColor(TDF::Color(255, 255, 255));
	m_newGameB.m_text->setText("New Game");
	m_newGameB.fitText();
	m_newGameB.m_renderDebug = true;
	

	//quit game button
	m_quitGameB.init();
	m_quitGameB.m_position.x = 870;
	m_quitGameB.m_position.y = 700;

	//quit game button text
	m_quitGameB.m_text = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Text>("..\\resources\\fonts\\Perpetua.ttf");
	m_quitGameB.m_text->resizeText(48);
	m_quitGameB.m_text->setColor(TDF::Color(255, 255, 255));
	m_quitGameB.m_text->setText("Quit");
	m_quitGameB.fitText();
	m_quitGameB.m_renderDebug = true;

	//quit world and add actor
	m_world.init();
	m_world.addActor(&m_newGameB);
	m_world.addActor(&m_quitGameB);

	//music
	m_titleTheme = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Music>("..\\resources\\music\\Title.wav");

	//button sfx
	m_newGameB.m_selection = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Sfx>("..\\resources\\sfx\\ui_change_selection.wav");
	m_quitGameB.m_selection = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Sfx>("..\\resources\\sfx\\ui_change_selection.wav");

	m_newGameB.m_activation = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Sfx>("..\\resources\\sfx\\ui_button_confirm.wav");
	m_quitGameB.m_activation = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Sfx>("..\\resources\\sfx\\ui_button_confirm.wav");

	//test animation
	m_grassAnimation = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Animation>("..\\resources\\animations\\grass.xml");

	m_titleTheme->play();
	m_grassAnimation->play(true);
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
	m_grassAnimation->setAlpha(m_lightAlpha);

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

	m_grassAnimation->update();
}

void MainMenu::render()
{
	//test anim
	TDF::RenderManager::GetInstance().renderAnimation(m_grassAnimation, 1000, 830);

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

	TDF::AudioManager::GetInstance().stopMusic();
	m_titleTheme->play();

	m_grassAnimation->play(true);
}