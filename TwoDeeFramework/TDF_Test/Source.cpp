#include <windows.h>	
#include <TDF.h>
#include "Player.h"

TDF::SDL_Manager* g_SDLManager;
TDF::ResourceManager* g_ResourceManager;
TDF::BoidManager* g_BoidManager;
TDF::RenderManager* g_RenderManager;
TDF::Box2DManager* g_Box2DManager;
TDF::InputManager* g_InputManager;
TDF::WorldManager* g_WorldManager;
TDF::SystemManager* g_SystemManager;
TDF::AudioManager* g_AudioManager;

#ifdef _WIN64

#else
TDF::AnttweakbarManager* g_AnttweakbarManager;
#endif

Uint64 g_time = SDL_GetPerformanceCounter();
Uint64 g_lastTime = 0;
float g_deltaTime = 0.0f;

int g_guiHandled;

TDF::World* g_World;
Player* g_player;
TDF::Music* g_music;

TDF::Timer g_timer;
std::string g_timeText;
TDF::Text* g_text;
int g_frames = 0;
float g_fps;

int g_levelWidth = 3840;
int g_levelHeight = 2160;

void initManagers()
{
	TDF::SDL_Manager::StartModule();
	g_SDLManager = TDF::SDL_Manager::GetPointerInstance();
	g_SDLManager->init();
	g_SDLManager->setWindowTitle("TwoDee");

	TDF::ResourceManager::StartModule();
	g_ResourceManager = TDF::ResourceManager::GetPointerInstance();

	TDF::BoidManager::StartModule();
	g_BoidManager = TDF::BoidManager::GetPointerInstance();

	TDF::RenderManager::StartModule();
	g_RenderManager = TDF::RenderManager::GetPointerInstance();
	g_RenderManager->init();

#ifdef _WIN64

#else
	TDF::AnttweakbarManager::StartModule();
	g_AnttweakbarManager = TDF::AnttweakbarManager::GetPointerInstance();
	g_AnttweakbarManager->init();
#endif

	TDF::Box2DManager::StartModule();
	g_Box2DManager = TDF::Box2DManager::GetPointerInstance();
	g_Box2DManager->init();

	TDF::InputManager::StartModule();
	g_InputManager = TDF::InputManager::GetPointerInstance();

	TDF::WorldManager::StartModule();
	g_WorldManager = TDF::WorldManager::GetPointerInstance();

	TDF::SystemManager::StartModule();
	g_SystemManager = TDF::SystemManager::GetPointerInstance();

	g_InputManager->subscribe(TDF::SYSTEM_INPUT, 0);

	TDF::AudioManager::StartModule();
	g_AudioManager = TDF::AudioManager::GetPointerInstance();
	g_AudioManager->init();
}

void initContent()
{
	g_World = new TDF::World();
	g_World->m_allActors.push_back(new Player());
	g_World->m_physicsWorld = g_Box2DManager->m_allWorlds["moon"];

	g_player = reinterpret_cast<Player*>(g_World->m_allActors.back());
	g_player->m_id = 2;
	g_player->world = g_World->m_physicsWorld;

	for (size_t i = 0; i < g_World->m_allActors.size(); i++)
	{
		g_World->m_allActors.at(i)->init();
	}

	g_WorldManager->setActiveWorld(g_World);

	g_AnttweakbarManager->hideBars(true);

	g_music = g_ResourceManager->loadFromFile<TDF::Music>("..\\resources\\music\\test.mp3");

	g_text = g_ResourceManager->loadFromFile<TDF::Text>("..\\resources\\fonts\\OptimusPrinceps.ttf");
}

void render()
{
	g_RenderManager->setRenderTarget(g_RenderManager->m_renderTargets[TDF::GBUFFER]);
	g_RenderManager->setRenderDrawColor(0xFF, 0xFF, 0xFF);
	g_RenderManager->renderClear();

	g_WorldManager->m_activeWorld->render();

	//g_BoidManager->render();

	g_timeText = "FPS: " + std::to_string(g_fps);
	g_RenderManager->renderText(g_text, g_timeText, 300, 20);

#ifdef _WIN64

#else
	g_AnttweakbarManager->render();
#endif

	g_RenderManager->setRenderTarget();
	g_RenderManager->setRenderDrawColor(0xFF, 0xFF, 0xFF);
	g_RenderManager->renderClear();

	//g_RenderManager->saveTextureAsPNG("test", g_RenderManager->m_renderTargets[TDF::GBUFFER]);
	g_RenderManager->renderTexture(g_RenderManager->m_renderTargets[TDF::GBUFFER], 0, 0);

	g_RenderManager->renderPresent();
}

void update(float _deltaTime)
{
	g_InputManager->update();
	g_SDLManager->update(_deltaTime);
	g_BoidManager->update(_deltaTime);
	g_WorldManager->m_activeWorld->update(_deltaTime);
}

void handleInputs()
{
	while (SDL_PollEvent(&g_SDLManager->m_events))
	{

#ifdef _WIN64
		g_guiHandled = 0;
#else
		g_AnttweakbarManager->handleEvent(&g_SDLManager->m_events);
		g_guiHandled = g_AnttweakbarManager->m_handled;
#endif
		
		if (!g_guiHandled)
		{
			g_InputManager->pollEvent(g_SDLManager->m_events);
		}
	}
}

int main()
{
	g_timer.start();

	initManagers();

	initContent();

	g_music->play();

	while (!g_SystemManager->m_quit)
	{
		g_lastTime = g_time;
		g_time = SDL_GetPerformanceCounter();

		g_deltaTime = (float)((g_time - g_lastTime) * 1000.0f / SDL_GetPerformanceFrequency());
		g_deltaTime /= 1000.0f;

		g_deltaTime = 1 / 60.0f;

		g_fps = g_frames / (g_timer.getTicks() / 1000.f);

		render();
		handleInputs();
		update(g_deltaTime);

		g_frames++;
	}

#ifdef _WIN64

#else
	g_AnttweakbarManager->release();
#endif
	
	g_SDLManager->release();
	g_AudioManager->release();

	return 0;
}