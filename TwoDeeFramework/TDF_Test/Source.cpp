#include <cstdio>
#include <windows.h>

#include <TDF.h>
#include <SB.h>
#include "Player.h"

TDF::SDL_Manager* g_SDLManager;
TDF::ResourceManager* g_ResourceManager;

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

void initSDL()
{
	TDF::SDL_Manager::StartModule();
	g_SDLManager = TDF::SDL_Manager::GetPointerInstance();
	g_SDLManager->init();
	SDL_SetWindowTitle(g_SDLManager->m_window, "Test");

	TDF::ResourceManager::StartModule();
	g_ResourceManager = TDF::ResourceManager::GetPointerInstance();
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
}

void render()
{
	SDL_SetRenderDrawColor(g_SDLManager->m_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(g_SDLManager->m_renderer);

	g_player.render();

#ifdef _WIN64

#else
	g_AnttweakbarManager->render();
#endif

	SDL_RenderPresent(g_SDLManager->m_renderer);
}

void update(float _deltaTime)
{
	g_SDLManager->update(_deltaTime);
	g_ResourceManager->update(_deltaTime);
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
					SDL_GetWindowSize(g_SDLManager->m_window, &g_SDLManager->m_windowWidth, &g_SDLManager->m_windowHeight);
#ifdef _WIN64

#else
					TwWindowSize(g_SDLManager->m_windowWidth, g_SDLManager->m_windowHeight);
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