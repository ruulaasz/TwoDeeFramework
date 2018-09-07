#pragma once

#include <queue>
#include <unordered_map>
#include "Module.h"
#include "SDL_Manager.h"
#include "InputMessage.h"

namespace TDF
{
	class InputManager : public Module<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		void queueMessage(const InputMessage& _message);

		void subscribe(messageType _type, int _id);

		void update();

		void sendMessage(const InputMessage& _message, int _id);

		void pollEvent(SDL_Event _event);

		std::queue<InputMessage> m_messageQueue;

		std::unordered_map<messageType, int> m_subscribers;

		InputMessage m_message;
	};
}