#include "InputManager.h"
#include "SceneManager.h"
#include "AnttweakbarManager.h"
#include "SystemManager.h"

namespace TDF
{
	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	void InputManager::queueMessage(const InputMessage & _message)
	{
		m_messageQueue.push(_message);
	}

	void InputManager::subscribe(messageType _type, int _id)
	{
		std::pair<int, messageType> newMessage(_id, _type);
		m_subscribers.insert(newMessage);
	}

	void InputManager::update()
	{
		while (!m_messageQueue.empty())
		{
			for (auto it = m_subscribers.begin(); it != m_subscribers.end(); ++it)
			{
				if (it->second == m_messageQueue.back().m_type)
				{
					sendMessage(m_messageQueue.back(), it->first);
				}
			}

			m_messageQueue.pop();
		}
	}

	void InputManager::sendMessage(const InputMessage & _message, int _id)
	{
		if (_message.m_type != SYSTEM_INPUT)
		{
			Actor* actor = SceneManager::GetInstance().getActor(_id);

			if (actor)
			{
				actor->dispatchMessage(_message);
			}
		}
		
		SystemManager::GetInstance().dispatchMessage(_message);
	}

	void InputManager::pollEvent(SDL_Event _event)
	{
		switch (_event.type)
		{
		default:
			break;

		case SDL_WINDOWEVENT:
			switch (_event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				break;
			}
			break;

		case SDL_QUIT:
			m_message.m_type = SYSTEM_INPUT;
			m_message.m_data.event = _event;
			queueMessage(m_message);
			break;

		case SDL_MOUSEBUTTONDOWN:
			m_message.m_type = MOUSE_INPUT;
			m_message.m_data.event = _event;
			queueMessage(m_message);
			break;

		case SDL_KEYDOWN:
			switch (_event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_message.m_type = SYSTEM_INPUT;
				m_message.m_data.event = _event;
				queueMessage(m_message);
				break;

			case SDLK_LALT:
				m_message.m_type = SYSTEM_INPUT;
				m_message.m_data.event = _event;
				queueMessage(m_message);
				break;

			case SDLK_RETURN:
				m_message.m_type = SYSTEM_INPUT;
				m_message.m_data.event = _event;
				queueMessage(m_message);
				break;

			default:
				m_message.m_type = KEYBOARD_INPUT;
				m_message.m_data.event = _event;
				queueMessage(m_message);
				break;
			}
			break;

		case SDL_KEYUP:
			switch (_event.key.keysym.sym)
			{
			case SDLK_LALT:
				m_message.m_type = SYSTEM_INPUT;
				m_message.m_data.event = _event;
				queueMessage(m_message);
				break;

			default:
				m_message.m_type = KEYBOARD_INPUT;
				m_message.m_data.event = _event;
				queueMessage(m_message);
				break;
			}
			break;

		case SDL_CONTROLLERAXISMOTION:
			if (_event.caxis.which == 0)
			{
				m_message.m_type = CONTROLLER_INPUT;
				m_message.m_data.event = _event;
				queueMessage(m_message);
			}
			break;

		case SDL_CONTROLLERBUTTONDOWN:
				m_message.m_type = CONTROLLER_INPUT;
				m_message.m_data.event = _event;
				queueMessage(m_message);
			break;

		case SDL_CONTROLLERBUTTONUP:
			m_message.m_type = CONTROLLER_INPUT;
			m_message.m_data.event = _event;
			queueMessage(m_message);
			break;
		}
	}

	void InputManager::pushEvent(SDL_Event _event)
	{
		pollEvent(_event);
	}
}