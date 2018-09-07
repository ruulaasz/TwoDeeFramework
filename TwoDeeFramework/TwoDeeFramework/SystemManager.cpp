#include "SystemManager.h"
#include "AnttweakbarManager.h"

namespace TDF
{
	SystemManager::SystemManager()
	{
		m_quit = false;
		m_altPressed = false;
	}

	SystemManager::~SystemManager()
	{

	}

	void SystemManager::dispatchMessage(const InputMessage & _message)
	{
		if (_message.m_data.event.type == SDL_WINDOWEVENT)
		{
			switch (_message.m_data.event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				break;
			}
		}

		if (_message.m_data.event.type == SDL_QUIT)
		{
			m_quit = true;
		}

		if (_message.m_data.event.type == SDL_KEYDOWN)
		{
			switch (_message.m_data.event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_quit = true;
				break;

			case SDLK_LALT:
				m_altPressed = true;
				break;

			case SDLK_RETURN:
				if (m_altPressed)
				{
					SDL_Manager::GetInstance().m_fullscreen ^= 1;
					SDL_Manager::GetInstance().setFullscreen(SDL_Manager::GetInstance().m_fullscreen);
					SDL_Manager::GetInstance().updateWindowSize();

#ifdef _WIN64

#else
					AnttweakbarManager::GetInstance().updateWindowSize();
#endif

				}
				break;
			}
		}

		if (_message.m_data.event.type == SDL_KEYUP)
		{
			switch (_message.m_data.event.key.keysym.sym)
			{
			case SDLK_LALT:
				m_altPressed = false;
				break;

			}
		}
	}
}