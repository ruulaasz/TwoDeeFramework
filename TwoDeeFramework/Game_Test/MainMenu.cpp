#include "MainMenu.h"

MainMenu::MainMenu()
{
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
	TDF::Scene::onEnter();

	//reset light effect
	m_lightAlpha = 240;
	m_alphaTarget = 0;

	//reset buttons
	m_newGameB.m_pressed = false;
	m_quitGameB.m_pressed = false;

	//reset animations
	m_selectAnim->play();
	m_grassAnim->play();
}

void MainMenu::onExit()
{
	TDF::Scene::onExit();
}

float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

void MainMenu::update(float _deltaTime)
{
	TDF::Scene::update(_deltaTime);

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

	//button select light
	TDF::RenderManager::GetInstance().renderAnimation(m_selectAnim, 
													  static_cast<int>(m_selectPosition.x),
													  static_cast<int>(m_selectPosition.y),
													  0.f, 
													  0.5f);

	//actores de la escena en este caso los botones
	TDF::Scene::render();
}

void MainMenu::init(TDF::PhysicsWorld* _physicWorld)
{
	//añadimos los actores al mundo
	m_world.addActor(&m_newGameB);
	m_world.addActor(&m_quitGameB);

	//se inicializa la escena asignandole un mundo fisico
	TDF::Scene::init(_physicWorld);

	m_lightAlpha = 240;
	m_alphaTarget = 0;

	//background
	m_background[0] = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("textures\\abyss_wall.png");
	m_background[1] = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("textures\\mainmenu_background_0.png");
	m_background[2] = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("textures\\lighthouse_light.png");
	m_background[3] = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("textures\\bone_bench_lit.png");
	m_background[4] = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("textures\\title.png");

	//new game button
	m_newGameB.m_position.x = 860;
	m_newGameB.m_position.y = 600;

	//new game button text
	m_newGameB.m_text.get()->m_font = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Font>("fonts\\Perpetua.ttf");
	m_newGameB.m_text.get()->resizeText(48);
	m_newGameB.m_text.get()->setColor(TDF::Color(255, 255, 255));
	m_newGameB.m_text.get()->setText("New Game");
	m_newGameB.fitText();
	m_newGameB.m_renderDebug = true;

	//quit game button
	m_quitGameB.m_position.x = 910;
	m_quitGameB.m_position.y = 700;

	//quit game button text
	m_quitGameB.m_text.get()->m_font = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Font>("fonts\\Perpetua.ttf");
	m_quitGameB.m_text->setColor(TDF::Color(255, 255, 255));
	m_quitGameB.m_text->setText("Quit");
	m_quitGameB.fitText();
	m_quitGameB.m_renderDebug = true;

	//music
	m_backgroundMusic = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Music>("music\\Title.wav");

	//button sfx
	m_newGameB.m_selectionSFX = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Sfx>("sfx\\ui_change_selection.wav");
	m_quitGameB.m_selectionSFX = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Sfx>("sfx\\ui_change_selection.wav");

	m_newGameB.m_activationSFX = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Sfx>("sfx\\ui_button_confirm.wav");
	m_quitGameB.m_activationSFX = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Sfx>("sfx\\ui_button_confirm.wav");

	//animations
	m_selectAnim = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Animation>("animations\\light.xml");
	m_selectAnim->setAnimationSpeed(0.09f);
	m_selectPosition.y = 200;
	m_selectAnim->play();

	m_grassAnim = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Animation>("animations\\grass.xml");
	m_grassAnim->play();
}

void MainMenu::checkButtons()
{
	if (m_newGameB.m_pressed)
	{
		TDF::SceneManager::GetInstance().setActiveScene("Level0");
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
	m_background[2]->setAlpha(static_cast<Uint8>(m_lightAlpha));
	m_background[3]->setAlpha(static_cast<Uint8>(m_lightAlpha));
	m_grassAnim->setAlpha(static_cast<Uint8>(m_lightAlpha));

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