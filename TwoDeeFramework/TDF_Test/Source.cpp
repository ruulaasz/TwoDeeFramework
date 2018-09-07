#include <cstdio>
#include <windows.h>	
#include <TDF.h>
#include "Player.h"

TDF::SDL_Manager* g_SDLManager;
TDF::ResourceManager* g_ResourceManager;
TDF::BoidManager* g_BoidManager;
TDF::RenderManager* g_RenderManager;
TDF::Box2DManager* g_Box2DManager;

#ifdef _WIN64

#else
TDF::AnttweakbarManager* g_AnttweakbarManager;
#endif

Uint64 g_time = SDL_GetPerformanceCounter();
Uint64 g_lastTime = 0;
float g_deltaTime = 0.0f;

bool g_quit;
bool g_lAlt;
int g_guiHandled;

TDF::World g_testWorld;
Player* g_player;

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
}

void initContent()
{
	g_testWorld.init();
	g_testWorld.m_allActors.push_back(new Player());
	g_player = reinterpret_cast<Player*>(g_testWorld.m_allActors.back());

	g_testWorld.m_physicsWorld = g_Box2DManager->m_allWorlds["moon"];

	g_player->world = g_testWorld.m_physicsWorld;

	for (size_t i = 0; i < g_testWorld.m_allActors.size(); i++)
	{
		g_testWorld.m_allActors.at(i)->init();
	}

	g_AnttweakbarManager->hideBars(true);
}

void render()
{
	g_RenderManager->setRenderTarget(g_RenderManager->m_renderTargets[TDF::GBUFFER]);
	g_RenderManager->setRenderDrawColor(0xFF, 0xFF, 0xFF);
	g_RenderManager->renderClear();

	g_testWorld.render();

	g_BoidManager->render();

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
	g_SDLManager->update(_deltaTime);
	g_BoidManager->update(_deltaTime);

	g_testWorld.update(_deltaTime);
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
			if (g_SDLManager->m_events.type == SDL_WINDOWEVENT)
			{
				switch (g_SDLManager->m_events.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					g_SDLManager->updateWindowSize();
#ifdef _WIN64

#else
					g_AnttweakbarManager->updateWindowSize();
#endif
					break;
				}
			}

			if (g_SDLManager->m_events.type == SDL_QUIT)
			{
				g_quit = true;
			}

			if (g_SDLManager->m_events.type == SDL_KEYDOWN)
			{
				switch (g_SDLManager->m_events.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					g_quit = true;
					break;

				case SDLK_LALT:
					g_lAlt = true;
					break;

				case SDLK_d:
					g_player->moveState = MS_RIGHT;
					break;

				case SDLK_a:
					g_player->moveState = MS_LEFT;
					break;

				case SDLK_w:
					g_player->jump();
					break;

				case SDLK_s:
					break;

				case SDLK_RETURN:
					if (g_lAlt)
					{
						g_SDLManager->m_fullscreen ^= 1;
						g_SDLManager->setFullscreen(g_SDLManager->m_fullscreen);
					}
					break;
				}
			}

			if (g_SDLManager->m_events.type == SDL_KEYUP)
			{
				switch (g_SDLManager->m_events.key.keysym.sym)
				{
				case SDLK_LALT:
					g_lAlt = false;
					break;

				case SDLK_d:
					g_player->moveState = MS_STOP;
					break;

				case SDLK_a:
					g_player->moveState = MS_STOP;
					break;

				case SDLK_w:
					break;

				case SDLK_s:
					break;
				}
			}
		}
	}
}

int main()
{
	initManagers();

	initContent();

	while (!g_quit)
	{
		g_lastTime = g_time;
		g_time = SDL_GetPerformanceCounter();

		g_deltaTime = (float)((g_time - g_lastTime) * 1000.0f / SDL_GetPerformanceFrequency());
		g_deltaTime /= 1000.0f;

		g_deltaTime = 1 / 60.0f;

		render();
		handleInputs();
		update(g_deltaTime);
	}

#ifdef _WIN64

#else
	g_AnttweakbarManager->release();
#endif
	
	g_SDLManager->release();

	return 0;
}