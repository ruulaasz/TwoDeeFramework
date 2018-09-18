#include <TDF.h>
#include "MainMenu.h"

TDF::SDL_Manager* g_SDLManager;
TDF::ResourceManager* g_ResourceManager;
TDF::BoidManager* g_BoidManager;
TDF::RenderManager* g_RenderManager;
TDF::Box2DManager* g_Box2DManager;
TDF::InputManager* g_InputManager;
TDF::SceneManager* g_SceneManager;
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

MainMenu g_mainMenu;

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

	TDF::SceneManager::StartModule();
	g_SceneManager = TDF::SceneManager::GetPointerInstance();

	TDF::SystemManager::StartModule();
	g_SystemManager = TDF::SystemManager::GetPointerInstance();

	TDF::AudioManager::StartModule();
	g_AudioManager = TDF::AudioManager::GetPointerInstance();
	g_AudioManager->init();

	g_InputManager->subscribe(TDF::SYSTEM_INPUT, 0);

	g_AnttweakbarManager->hideBars(true);
}

void initContent()
{
	g_mainMenu.onEnter();
	g_SceneManager->setActiveScene(&g_mainMenu);
}

void render()
{
	g_RenderManager->setRenderTarget(g_RenderManager->m_renderTargets[TDF::GBUFFER]);
	g_RenderManager->setRenderDrawColor(0, 0, 0);
	g_RenderManager->renderClear();

	g_SceneManager->m_activeScene->render();

	g_BoidManager->render();

#ifdef _WIN64

#else
	g_AnttweakbarManager->render();
#endif

	g_RenderManager->setRenderTarget();
	g_RenderManager->setRenderDrawColor(0, 0, 0);
	g_RenderManager->renderClear();

	g_RenderManager->renderTexture(g_RenderManager->m_renderTargets[TDF::GBUFFER], 0, 0);

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

void close()
{

#ifdef _WIN64

#else
	g_AnttweakbarManager->release();
#endif

	g_SDLManager->release();
	g_AudioManager->release();
}

int main()
{
	initManagers();

	initContent();

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