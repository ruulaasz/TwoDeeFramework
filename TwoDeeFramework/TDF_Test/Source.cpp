#include <cstdio>
#include <windows.h>

#include <TDF.h>
#include "Player.h"

TDF::SDL_Manager* g_SDLManager;
TDF::ResourceManager* g_ResourceManager;
TDF::AnttweakbarManager* g_AnttweakbarManager;

Uint64 g_time = SDL_GetPerformanceCounter();
Uint64 g_lastTime = 0;
float g_deltaTime = 0;

bool g_quit;
bool g_lAlt;
bool g_resize;
int g_mousePosX;
int g_mousePosY;

Player g_player;
TwBar *g_myBar;

void initSDL()
{
	TDF::SDL_Manager::StartModule();
	g_SDLManager = TDF::SDL_Manager::GetPointerInstance();
	g_SDLManager->init();
	SDL_SetWindowTitle(g_SDLManager->m_window, "Test");

	TDF::ResourceManager::StartModule();
	g_ResourceManager = TDF::ResourceManager::GetPointerInstance();
}

void initTw()
{
	TDF::AnttweakbarManager::StartModule();
	g_AnttweakbarManager = TDF::AnttweakbarManager::GetPointerInstance();
	g_AnttweakbarManager->init();
}

void GUIinit()
{
	g_myBar = g_AnttweakbarManager->createBar(TEXT("Mouse_position"));
	g_AnttweakbarManager->addBar(g_myBar, TEXT("mouse posX:"), TW_TYPE_INT32, &g_AnttweakbarManager->m_handled, TEXT(" label='Mouse posX' "));
}

void loadContent()
{
	g_player.init();
}

void render()
{
	SDL_SetRenderDrawColor(g_SDLManager->m_renderer, 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(g_SDLManager->m_renderer);

	g_player.render();
	g_AnttweakbarManager->render();

	SDL_RenderPresent(g_SDLManager->m_renderer);
}

void update(float _deltaTime)
{
	SDL_GetMouseState(&g_mousePosX, &g_mousePosY);
	g_ResourceManager->update(_deltaTime);
}

void handleInputs()
{
	while (SDL_PollEvent(&g_SDLManager->m_events))
	{
		g_AnttweakbarManager->m_handled = TwEventSDL(&g_SDLManager->m_events, SDL_MAJOR_VERSION, SDL_MINOR_VERSION);
;
		if (!g_AnttweakbarManager->m_handled)
		{
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
						g_resize ^= 1;
						if (g_resize)
						{
							SDL_SetWindowFullscreen(g_SDLManager->m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
						}
						else
						{
							SDL_SetWindowFullscreen(g_SDLManager->m_window, 0);
						}
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
	initTw();
	loadContent();
	GUIinit();

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

	g_AnttweakbarManager->release();
	g_SDLManager->release();

	return 0;
}