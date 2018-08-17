#pragma once

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")

#include <SDL.h>
#include <SDL_image.h>
#include "Module.h"

namespace TDF
{
	//!  A manager class for SDL 2.0. 
	/*!
	Used to initialize and use the SDL 2.0 modules.
	*/
	class SDL_Manager : public Module<SDL_Manager>
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		SDL_Manager();

		//! Default destructor.
		/*!
		Does nothing use the release() function instead.
		*/
		~SDL_Manager();

		//! Initialize SDL 2.0 subsystems and creates the window and renderer.
		/*!
		\sa initSubSystems(), createWindowAndRenderer()
		*/
		void init();

		//! Shut down the SDL 2.0 subsystems and cleans the memory.
		/*!
		\sa ~SDL_Manager()
		*/
		void release();

	private:
		//! Initialize SDL 2.0 subsystems.
		/*!
		\sa init()
		*/
		void initSubSystems();

		//! Creates the window and renderer.
		/*!
		\param _name a constant character pointer, window name.
		\param _windowWidth an integer, the width of the window.
		\param _windowHeight an integer, the height of the window.
		\sa init()
		*/
		void createWindowAndRenderer(const char* _name = "New Window", int _windowWidth = 1280, int _windowHeight = 920);

	public:
		//! A pointer to a SDL renderer.
		SDL_Renderer* m_renderer;

		//! A pointer to a SDL window.
		SDL_Window* m_window;

		//! The SDL events.
		SDL_Event m_events;

		//! The width of the window.
		int m_windowWidth;

		//! The height of the window.
		int m_windowHeight;
	};
}