#include "Button.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "SceneManager.h"

namespace TDF
{
	Button::Button()
	{
		m_pressed = false;
		m_selected = false;
		m_renderDebug = true;
		m_audioPlayed = false;

		m_selectionSFX = nullptr;
		m_activationSFX = nullptr;
	}

	Button::~Button()
	{

	}

	void Button::update(float _deltaTime)
	{
		_deltaTime;

		//get the mouse
		SDL_Point p;
		p.x = SDL_Manager::GetInstance().m_mousePosX;
		p.y = SDL_Manager::GetInstance().m_mousePosY;

		//make the rect for collition
		m_rect.h = static_cast<int>(m_dimentions.y);
		m_rect.w = static_cast<int>(m_dimentions.x);
		m_rect.x = static_cast<int>(m_position.x);
		m_rect.y = static_cast<int>(m_position.y);

		//check if mouse is in rect
		m_selected = SDL_PointInRect(&p, &m_rect);

		if (m_selected)
		{
			if (!m_audioPlayed)
			{
				if (m_selectionSFX)
				{
					m_selectionSFX.get()->play(-1);
				}



				m_audioPlayed = true;
			}
		}
		else
		{
			m_audioPlayed = false;
		}
	}

	void Button::render()
	{
		if (m_renderDebug)
		{
			if (m_selected)
			{
				RenderManager::GetInstance().setRenderDrawColor(Color(0, 255, 0));
			}
			else
			{
				RenderManager::GetInstance().setRenderDrawColor(Color(255, 255, 255));
			}

			if (m_pressed)
			{
				RenderManager::GetInstance().setRenderDrawColor(Color(255, 0, 0));
			}

			SDL_RenderDrawRect(SDL_Manager::GetInstance().m_renderer, &m_rect);
		}
	}

	void Button::init()
	{
		InputManager::GetInstance().subscribe(MOUSE_INPUT, m_id);
	}

	void Button::dispatchMessage(const InputMessage & _message)
	{
		switch (_message.m_data.event.type)
		{
		default:
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (_message.m_data.event.button.button == SDL_BUTTON_LEFT)
			{
				if (m_selected)
				{
					m_pressed = true;

					if (m_activationSFX)
					{
						m_activationSFX.get()->play(-1);
					}
				}
			}
			break;
		}
	}
}