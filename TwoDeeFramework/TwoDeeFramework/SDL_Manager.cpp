#include "SDL_Manager.h"
#include <cstdio>

namespace TDF
{
	SDL_Manager::SDL_Manager()
	{
		m_renderer = nullptr;
		m_window = nullptr;
	}

	SDL_Manager::~SDL_Manager()
	{

	}

	void SDL_Manager::init()
	{
		initSubSystems();
		createWindow();
	}

	void SDL_Manager::release()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
		m_renderer = nullptr;

		IMG_Quit();
		SDL_Quit();
	}

	void SDL_Manager::initSubSystems()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL_Init VIDEO failed: %s\n", SDL_GetError());
		}

		IMG_Init(IMG_INIT_PNG);

		if (SDL_Init(SDL_INIT_AUDIO) < 0)
		{
			printf("SDL_Init AUDIO failed: %s\n", SDL_GetError());
		}
	}

	void SDL_Manager::createWindow(const char * _name, int _windowWidth, int _windowHeight)
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		
		m_window = SDL_CreateWindow(_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _windowWidth, _windowHeight, SDL_WINDOW_RESIZABLE);
		if (!m_window)
		{
			printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
		}

		m_windowHeight = _windowHeight;
		m_windowWidth = _windowWidth;

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}
}