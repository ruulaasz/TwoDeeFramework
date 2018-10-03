#include <TDF.h>
#include "MainMenu.h"
#include "Level_0.h"

TDF::SDL_Manager* g_SDLManager;
TDF::ResourceManager* g_ResourceManager;
TDF::BoidManager* g_BoidManager;
TDF::RenderManager* g_RenderManager;
TDF::Box2DManager* g_Box2DManager;
TDF::InputManager* g_InputManager;
TDF::SceneManager* g_SceneManager;
TDF::SystemManager* g_SystemManager;
TDF::AudioManager* g_AudioManager;
TDF::AnttweakbarManager* g_AnttweakbarManager;

Uint64 g_time = SDL_GetPerformanceCounter();
Uint64 g_lastTime = 0;
float g_deltaTime = 0.0f;

int g_guiHandled;

MainMenu g_mainMenu;
Level_0 g_level0;

void initManagers()
{
	TDF::SDL_Manager::StartModule();
	g_SDLManager = TDF::SDL_Manager::GetPointerInstance();
	g_SDLManager->init();
	g_SDLManager->setWindowTitle("Game_Test");

	TDF::ResourceManager::StartModule();
	g_ResourceManager = TDF::ResourceManager::GetPointerInstance();

	TDF::BoidManager::StartModule();
	g_BoidManager = TDF::BoidManager::GetPointerInstance();

	TDF::RenderManager::StartModule();
	g_RenderManager = TDF::RenderManager::GetPointerInstance();
	g_RenderManager->init();

	TDF::AnttweakbarManager::StartModule();
	g_AnttweakbarManager = TDF::AnttweakbarManager::GetPointerInstance();
	g_AnttweakbarManager->init();

	TDF::Box2DManager::StartModule();
	g_Box2DManager = TDF::Box2DManager::GetPointerInstance();
	g_Box2DManager->init();

	TDF::InputManager::StartModule();
	g_InputManager = TDF::InputManager::GetPointerInstance();

	TDF::SceneManager::StartModule();
	g_SceneManager = TDF::SceneManager::GetPointerInstance();

	TDF::SystemManager::StartModule();
	g_SystemManager = TDF::SystemManager::GetPointerInstance();

	TDF::AudioManager::StartModule();
	g_AudioManager = TDF::AudioManager::GetPointerInstance();
	g_AudioManager->init();

	g_InputManager->subscribe(TDF::SYSTEM_INPUT, 0);
}

void initScenes()
{
	g_Box2DManager->m_allWorlds["moon"] = g_Box2DManager->createWorld("moon", TDF::Vector2D(0.0f, 18.5f));

	g_SceneManager->m_allScenes["MainMenu"] = &g_mainMenu;
	g_SceneManager->m_allScenes["MainMenu"]->init();

	g_SceneManager->m_allScenes["Level0"] = &g_level0;
	g_SceneManager->m_allScenes["Level0"]->init(g_Box2DManager->getWorld("moon"));

	g_SceneManager->setActiveScene("MainMenu");
}

void render()
{
	g_RenderManager->setRenderTarget(g_RenderManager->m_renderTargets[TDF::GBUFFER]);
	g_RenderManager->setRenderDrawColor(TDF::Color(0, 0, 0));
	g_RenderManager->renderClear();

	g_SceneManager->m_activeScene->render();

	g_BoidManager->render();

	g_AnttweakbarManager->render();

	g_RenderManager->setRenderTarget();
	g_RenderManager->setRenderDrawColor(TDF::Color(0, 0, 0));
	g_RenderManager->renderClear();

	g_RenderManager->renderTexture(g_RenderManager->m_renderTargets[TDF::GBUFFER],0, 0);

	//g_RenderManager->saveTextureAsPNG("test", g_RenderManager->m_renderTargets[TDF::GBUFFER]);

	g_RenderManager->renderPresent();
}

void update(float _deltaTime)
{
	g_InputManager->update();
	g_SDLManager->update(_deltaTime);
	g_BoidManager->update(_deltaTime);
	g_SceneManager->m_activeScene->update(_deltaTime);
}

void handleInputs()
{
	while (SDL_PollEvent(&g_SDLManager->m_events))
	{
		g_guiHandled = 0;

		g_AnttweakbarManager->handleEvent(&g_SDLManager->m_events);
		g_guiHandled = g_AnttweakbarManager->m_handled;

		if (!g_guiHandled)
		{
			g_InputManager->pollEvent(g_SDLManager->m_events);
		}
	}
}

void close()
{
	g_AnttweakbarManager->release();
	g_SDLManager->release();
	g_AudioManager->release();
}

int main()
{
	initManagers();

	g_AnttweakbarManager->hideBars(false);

	initScenes();

	//g_ResourceManager->printDebug();

	while (!g_SystemManager->m_quit)
	{
		g_deltaTime = 1 / 60.0f;

		render();
		handleInputs();
		update(g_deltaTime);
	}

	close();

	return 0;
}