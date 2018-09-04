#pragma once

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")

#include <SDL.h>
#include <SDL_image.h>
#include "Module.h"

namespace TDF
{
	class Texture;

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
		\sa release()
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

		//! Update the manager.
		/*!
		\param _deltaTime a float, the change of time.
		*/
		void update(float _deltaTime);

		//! Creates the window and renderer.
		/*!
		\param _fullscreen an integer, 0 for windowed 1 for fullscreen.
		*/
		void setFullscreen(int _fullscreen);

		//! Change the size of the window.
		/*!
		\param _w an integer, the new width of the window.
		\param _h an integer, the new height of the window.
		*/
		void resizeWindow(int _w, int _h);

	private:
		//! Initialize SDL 2.0 subsystems.
		/*!
		\sa init()
		*/
		void initSubSystems();

		//! Creates the window and renderer.
		/*!
		\param _name a constant character pointer, the window name.
		\param _windowWidth an integer, the width of the window.
		\param _windowHeight an integer, the height of the window.
		\sa init()
		*/
		void createWindowAndRenderer(const char* _name = "New Window", int _windowWidth = 1920, int _windowHeight = 1000);

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

		//! If the window is fullscreen.
		bool m_fullscreen;

		//! The X position of the mouse.
		int m_mousePosX;

		//! The Y position of the mouse.
		int m_mousePosY;
	};
}