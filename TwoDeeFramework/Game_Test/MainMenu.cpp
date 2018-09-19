#include "MainMenu.h"

MainMenu::MainMenu()
{
	for (size_t i = 0; i < BACKGROUND_TEXTURES; i++)
	{
		m_background[i] = nullptr;
	}

	m_titleMusic = nullptr;
	m_selectAnim = nullptr;
	m_grassAnim = nullptr;

	m_alphaTarget = 0;
	m_lightAlpha = 0;
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
	m_newGameB.m_position.x = 860;
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
	m_quitGameB.m_position.x = 910;
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
	m_titleMusic = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Music>("..\\resources\\music\\Title.wav");

	//button sfx
	m_newGameB.m_selectionSFX = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Sfx>("..\\resources\\sfx\\ui_change_selection.wav");
	m_quitGameB.m_selectionSFX = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Sfx>("..\\resources\\sfx\\ui_change_selection.wav");

	m_newGameB.m_activationSFX = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Sfx>("..\\resources\\sfx\\ui_button_confirm.wav");
	m_quitGameB.m_activationSFX = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Sfx>("..\\resources\\sfx\\ui_button_confirm.wav");

	//animations
	m_selectAnim = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Animation>("..\\resources\\animations\\light.xml");
	m_selectAnim->setAnimationSpeed(0.09f);
	m_selectPosition.y = 200;
	m_selectAnim->play();

	m_grassAnim = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Animation>("..\\resources\\animations\\grass.xml");
	m_grassAnim->play();

	m_titleMusic->play();
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
	//world update
	m_world.update(_deltaTime);

	lightEffect(_deltaTime);

	checkButtons();

	//animation
	m_selectAnim->update();
	m_grassAnim->update();
}

void MainMenu::render()
{
	TDF::RenderManager::GetInstance().renderAnimation(m_grassAnim, 980, 850);

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

	TDF::RenderManager::GetInstance().renderAnimation(m_selectAnim, 
													  static_cast<int>(m_selectPosition.x),
													  static_cast<int>(m_selectPosition.y),
													  0.f, 
													  0.5f);
}

void MainMenu::reset()
{
	//reset light effect
	m_lightAlpha = 240;
	m_alphaTarget = 0;

	m_newGameB.m_pressed = false;
	m_quitGameB.m_pressed = false;

	TDF::AudioManager::GetInstance().stopMusic();
	m_titleMusic->play();

	m_selectAnim->play();
	m_grassAnim->play();
}

void MainMenu::checkButtons()
{
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

	if (m_newGameB.m_selected)
	{
		m_selectPosition.x = 790;
		m_selectPosition.y = 580;
	}
	else if (m_quitGameB.m_selected)
	{
		m_selectPosition.x = 830;
		m_selectPosition.y = 680;
	}
	else
	{
		m_selectPosition.x = -100;
		m_selectPosition.y = -100;
	}
}

void MainMenu::lightEffect(float _deltaTime)
{
	m_background[2]->setAlpha(m_lightAlpha);
	m_background[3]->setAlpha(m_lightAlpha);
	m_grassAnim->setAlpha(m_lightAlpha);

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
}