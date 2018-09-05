#include <cstdio>
#include <windows.h>

#include <TDF.h>
#include "Player.h"

TDF::SDL_Manager* g_SDLManager;
TDF::ResourceManager* g_ResourceManager;
TDF::BoidManager* g_BoidManager;
TDF::RenderManager* g_RenderManager;

#ifdef _WIN64

#else
TDF::AnttweakbarManager* g_AnttweakbarManager;
#endif

Uint64 g_time = SDL_GetPerformanceCounter();
Uint64 g_lastTime = 0;
float g_deltaTime = 0;

bool g_quit;
bool g_lAlt;
int g_guiHandled;

Player g_player;
TDF::AABB g_wall;

void initSDL()
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
}

#ifdef _WIN64

#else
void initTw()
{
	TDF::AnttweakbarManager::StartModule();
	g_AnttweakbarManager = TDF::AnttweakbarManager::GetPointerInstance();
	g_AnttweakbarManager->init();
}
#endif

void loadContent()
{
	g_player.init();
	g_player.m_position = TDF::Vector2D(500, 500);

	g_wall = TDF::AABB(TDF::Vector2D(600, 0), 100, 1000);
}

void render()
{
	g_RenderManager->setRenderTarget(g_RenderManager->m_renderTargets[TDF::GBUFFER]);
	g_RenderManager->setRenderDrawColor(0xFF, 0xFF, 0xFF);
	g_RenderManager->renderClear();

	g_player.render();
	g_wall.render();

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

	g_player.update(_deltaTime);
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
					g_player.m_velocity = TDF::Vector2D(1, 0);
					break;

				case SDLK_a:
					g_player.m_velocity = TDF::Vector2D(-1, 0);
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
					g_player.m_velocity = TDF::Vector2D(0, 0);
					break;

				case SDLK_a:
					g_player.m_velocity = TDF::Vector2D(0, 0);
					break;
				}
			}
		}
	}
}

int main()
{
	initSDL();

#ifdef _WIN64

#else
	initTw();
#endif

	loadContent();

	while (!g_quit)
	{
		g_lastTime = g_time;
		g_time = SDL_GetPerformanceCounter();

		g_deltaTime = (float)((g_time - g_lastTime) * 1000 / SDL_GetPerformanceFrequency());
		g_deltaTime /= 1000.f;

		handleInputs();
		update(g_deltaTime);
		render();
	}

#ifdef _WIN64

#else
	g_AnttweakbarManager->release();
#endif
	
	g_SDLManager->release();
	return 0;
}