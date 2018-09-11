#include "SDL_Manager.h"
#include <cstdio>
#include "Texture.h"

namespace TDF
{
	SDL_Manager::SDL_Manager()
	{
		m_renderer = nullptr;
		m_window = nullptr;
		m_windowHeight = 0;
		m_windowWidth = 0;
		m_fullscreen = false;
		m_mousePosX = 0;
		m_mousePosY = 0;
		m_controller = nullptr;
	}

	SDL_Manager::~SDL_Manager()
	{

	}

	void SDL_Manager::init()
	{
		initSubSystems();
		createWindowAndRenderer();
	}

	void SDL_Manager::release()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
		m_renderer = nullptr;

		SDL_GameControllerClose(m_controller); 
		m_controller = nullptr;

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	void SDL_Manager::update(float _deltaTime)
	{
		_deltaTime;
		SDL_GetMouseState(&m_mousePosX, &m_mousePosY);
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

		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		}

		if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
		{
			printf("SDL_Init GAMECONTROLLER failed: %s\n", SDL_GetError());
		}
	}

	void SDL_Manager::createWindowAndRenderer(const char * _name, int _windowWidth, int _windowHeight)
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		
		m_window = SDL_CreateWindow(_name, 0, 30, _windowWidth, _windowHeight, SDL_WINDOW_SHOWN);

		if (!m_window)
		{
			printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
		}

		m_windowHeight = _windowHeight;
		m_windowWidth = _windowWidth;

		m_renderer = SDL_CreateRenderer(m_window, -1, 
									    SDL_RENDERER_ACCELERATED | 
									    SDL_RENDERER_TARGETTEXTURE | 
									    SDL_RENDERER_PRESENTVSYNC);

		//Check for joysticks 
		if( SDL_NumJoysticks() < 1 ) 
		{ 
			printf( "Warning: No joysticks connected!\n" ); 
		} 
		else
		{ //Load joystick 
			m_controller = SDL_GameControllerOpen( 0 );

			if(!m_controller)
			{ 
				printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
			} 
		}

		//SDL_GameControllerAddMappingsFromFile("..\\resources\\gamecontrollerdb.txt");
	}

	void SDL_Manager::updateWindowSize()
	{
		SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
	}

	void SDL_Manager::setWindowTitle(const char * _title)
	{
		SDL_SetWindowTitle(m_window, _title);
	}

	void SDL_Manager::setFullscreen(int _fullscreen)
	{
		if (_fullscreen)
		{
			SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else
		{
			SDL_SetWindowFullscreen(m_window, 0);
		}
	}

	void SDL_Manager::resizeWindow(int _w, int _h)
	{
		SDL_SetWindowSize(m_window, _w, _h);
	}
}