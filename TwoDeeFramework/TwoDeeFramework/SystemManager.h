#pragma once

#include "InputMessage.h"

namespace TDF
{
	class SystemManager : public Module<SystemManager>
	{
	public:
		SystemManager();
		~SystemManager();

		bool m_quit;
		bool m_altPressed;

		void dispatchMessage(const InputMessage& _message);
	};
}