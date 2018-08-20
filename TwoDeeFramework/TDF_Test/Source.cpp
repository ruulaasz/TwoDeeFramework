#pragma comment(lib, "AntTweakBar.lib")

#include <cstdio>
#include <windows.h>
#include <TDF.h>
#include <AntTweakBar.h>
#include "Player.h"

TDF::SDL_Manager* g_SDLManager;
TDF::ResourceManager* g_ResourceManager;

Uint64 g_time = SDL_GetPerformanceCounter();
Uint64 g_lastTime = 0;
float g_deltaTime = 0;

bool g_quit;
bool g_lAlt;
bool g_resize;
int g_mousePosX;
int g_mousePosY;

Player g_player;

int g_iTwhandled;
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
	TwInit(TW_DIRECT3D9, SDL_RenderGetD3D9Device(g_SDLManager->m_renderer));
	TwWindowSize(g_SDLManager->m_windowWidth, g_SDLManager->m_windowWidth);

	g_myBar = TwNewBar(TEXT("Mouse_position"));

	TwDefine(TEXT("Mouse_position color='255 128 255' alpha=180 "));
	TwDefine(TEXT("Mouse_position text=light "));
	TwDefine(TEXT("Mouse_position position='50 33' "));
	TwDefine(TEXT("Mouse_position size='250 290' "));
	TwDefine(TEXT("Mouse_position valueswidth=90 "));
	TwDefine(TEXT("Mouse_position refresh=0.01 "));
	TwDefine(" GLOBAL contained=true ");
}

void loadContent()
{
	g_player.init();

	TwAddVarRO(g_myBar, TEXT("mouse posX:"), TW_TYPE_INT32, &g_iTwhandled, TEXT(" label='Mouse posX' "));
}

void render()
{
	SDL_SetRenderDrawColor(g_SDLManager->m_renderer, 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(g_SDLManager->m_renderer);

	g_player.render();
	TwDraw();

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
		g_iTwhandled = TwEventSDL(&g_SDLManager->m_events, SDL_MAJOR_VERSION, SDL_MINOR_VERSION);
;
		if (!g_iTwhandled) 
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

	TwTerminate();
	g_SDLManager->release();

	return 0;
}