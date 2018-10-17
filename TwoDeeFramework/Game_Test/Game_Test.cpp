#include <TDF.h>
#include "MainMenu.h"
#include "Level_0.h"
#include "Level_1.h"
#include "Knight.h"

TDF::SDL_Manager* g_SDLManager;
TDF::ResourceManager* g_ResourceManager;
TDF::RenderManager* g_RenderManager;
TDF::Box2DManager* g_Box2DManager;
TDF::InputManager* g_InputManager;
TDF::SceneManager* g_SceneManager;
TDF::SystemManager* g_SystemManager;
TDF::AudioManager* g_AudioManager;
TDF::AnttweakbarManager* g_AnttweakbarManager;
TDF::CameraManager* g_CameraManager;

Uint64 g_time = SDL_GetPerformanceCounter();
Uint64 g_lastTime = 0;
float g_deltaTime = 0.0f;

int g_guiHandled;

Knight* g_player;
MainMenu* g_mainMenu;
Level_0* g_level0;
Level_1* g_level1;

void initManagers()
{
	TDF::SDL_Manager::StartModule();
	g_SDLManager = TDF::SDL_Manager::GetPointerInstance();
	g_SDLManager->init();
	g_SDLManager->setWindowTitle("Game_Test");

	TDF::ResourceManager::StartModule();
	g_ResourceManager = TDF::ResourceManager::GetPointerInstance();

	TDF::RenderManager::StartModule();
	g_RenderManager = TDF::RenderManager::GetPointerInstance();
	g_RenderManager->init();

	TDF::CameraManager::StartModule();
	g_CameraManager = TDF::CameraManager::GetPointerInstance();

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
}

void initScenes()
{
	g_player = new Knight();
	g_player->init();

	g_mainMenu = new MainMenu();
	g_level0 = new Level_0();
	g_level1 = new Level_1();

	g_SceneManager->m_allScenes["MainMenu"] = g_mainMenu;
	g_SceneManager->m_allScenes["MainMenu"]->init();

	g_level0->m_player = g_player;
	g_SceneManager->m_allScenes["Level0"] = g_level0;
	g_SceneManager->m_allScenes["Level0"]->init();

	g_level1->m_player = g_player;
	g_SceneManager->m_allScenes["Level1"] = g_level1;
	g_SceneManager->m_allScenes["Level1"]->init();

	g_SceneManager->setActiveScene("Level0");
}

void render()
{
	g_RenderManager->setRenderTarget(g_RenderManager->m_renderTargets[TDF::GBUFFER]);
	g_RenderManager->setRenderDrawColor(TDF::Color(0, 0, 0));
	g_RenderManager->renderClear();

	g_SceneManager->m_activeScene->render();

	g_AnttweakbarManager->render();

	g_RenderManager->setRenderTarget();
	g_RenderManager->setRenderDrawColor(TDF::Color(255, 255, 255));
	g_RenderManager->renderClear();

	g_RenderManager->renderTexture(g_RenderManager->m_renderTargets[TDF::GBUFFER],0, 0);

	//g_RenderManager->saveTextureAsPNG("test.png", g_RenderManager->m_renderTargets[TDF::GBUFFER]);

	g_RenderManager->renderPresent();
}

void update(float _deltaTime)
{
	g_InputManager->update();
	g_SDLManager->update(_deltaTime);
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

			//temp
			switch (g_SDLManager->m_events.type)
			{
			default:
				break;

			case SDL_KEYDOWN:
				switch (g_SDLManager->m_events.key.keysym.sym)
				{
				case SDLK_1:
					g_SceneManager->setActiveScene("MainMenu");
					break;

				case SDLK_2:
					g_SceneManager->setActiveScene("Level0");
					break;

				case SDLK_3:
					g_SceneManager->setActiveScene("Level1");
					break;
				}
				break;
			//
			}
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