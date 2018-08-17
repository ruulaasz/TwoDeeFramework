#pragma once

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")

#include <SDL.h>
#include <SDL_image.h>

namespace TDF
{
	class SDL_Manager
	{
	public:
		SDL_Manager();
		~SDL_Manager();

		void init();
		void release();

	private:
		void initSubSystems();
		void createWindow(const char* _name = "New Window", int _windowWidth = 1280, int _windowHeight = 920);

	public:
		SDL_Renderer* m_renderer;
		SDL_Window* m_window;
		SDL_Event m_events;

		int m_windowWidth;
		int m_windowHeight;
		const char* m_windowName;
	};
}