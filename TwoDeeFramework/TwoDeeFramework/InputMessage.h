#pragma once

#include "SDL_Manager.h"

namespace TDF
{
	enum messageType
	{
		CONTROLLER_INPUT=0,
		KEYBOARD_INPUT,
		MOUSE_INPUT,
		SYSTEM_INPUT
	};

	struct inputData
	{
		SDL_Event event;
		void* data;
	};

	class InputMessage
	{
	public:
		InputMessage();
		~InputMessage();

		messageType m_type;
		inputData m_data;
	};
}