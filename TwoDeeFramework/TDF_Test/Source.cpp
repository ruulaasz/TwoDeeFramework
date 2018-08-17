#include <cstdio>
#include <TDF.h>

TDF::SDL_Manager* g_SDLManager;

Uint64 g_time = SDL_GetPerformanceCounter();
Uint64 g_lastTime = 0;
double g_deltaTime = 0;

bool g_quit;
bool g_lAlt;
bool g_resize;

TDF::Texture testTexture;

void initSDL()
{
	TDF::SDL_Manager::StartModule();
	g_SDLManager = TDF::SDL_Manager::GetPointerInstance();
	g_SDLManager->init();
	SDL_SetWindowTitle(g_SDLManager->m_window, "Test");
}

void loadContent()
{
	testTexture.load("resources\\Untitled.png");
}

void render()
{
	SDL_SetRenderDrawColor(g_SDLManager->m_renderer, 0xFF, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(g_SDLManager->m_renderer);

	SDL_Rect renderQuad = { 0, 0, testTexture.m_width, testTexture.m_height };
	SDL_RenderCopy(g_SDLManager->m_renderer, testTexture.m_sdlTexture, &renderQuad, &renderQuad);

	SDL_RenderPresent(g_SDLManager->m_renderer);
}

void handleInputs()
{
	while (SDL_PollEvent(&g_SDLManager->m_events))
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

int main()
{
	initSDL();
	loadContent();

	while (!g_quit)
	{
		g_lastTime = g_time;
		g_time = SDL_GetPerformanceCounter();

		g_deltaTime = (double)((g_time - g_lastTime) * 1000 / SDL_GetPerformanceFrequency());
		g_deltaTime /= 1000.f;

		handleInputs();
		render();
	}

	g_SDLManager->release();

	return 0;
}