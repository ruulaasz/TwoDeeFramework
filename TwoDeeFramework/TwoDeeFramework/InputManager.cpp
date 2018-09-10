#include "InputManager.h"
#include "worldManager.h"
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
		std::pair<messageType, int> newMessage(_type, _id);
		m_subscribers.insert(newMessage);
	}

	void InputManager::update()
	{
		while (!m_messageQueue.empty())
		{
			for (auto it = m_subscribers.begin(); it != m_subscribers.end(); ++it)
			{
				if (it->first == m_messageQueue.back().m_type)
				{
					sendMessage(m_messageQueue.back(), it->second);
				}
			}

			m_messageQueue.pop();
		}
	}

	void InputManager::sendMessage(const InputMessage & _message, int _id)
	{
		if (_message.m_type != SYSTEM_INPUT)
		{
			WorldManager::GetInstance().getActor(_id)->dispatchMessage(_message);
		}
		
		SystemManager::GetInstance().dispatchMessage(_message);
	}

	void InputManager::pollEvent(SDL_Event _event)
	{
		if (_event.type == SDL_WINDOWEVENT)
		{
			switch (_event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				break;
			}
		}

		if (_event.type == SDL_QUIT)
		{
			m_message.m_type = SYSTEM_INPUT;
			m_message.m_data.event = _event;
			queueMessage(m_message);
		}

		if (_event.type == SDL_KEYDOWN)
		{
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
		}

		if (_event.type == SDL_KEYUP)
		{
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
		}
	}
}