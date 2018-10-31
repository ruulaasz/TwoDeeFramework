#pragma once

#include "InputMessage.h"

namespace TDF
{
	//!  A manager class for the System.
	class SystemManager : public Module<SystemManager>
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		SystemManager();

		//! Default destructor.
		~SystemManager();

		//! Dispatch a message.
		/*!
		\param _message, A message.
		*/
		void dispatchMessage(const InputMessage& _message);

	public:
		//! A flag to quit the application.
		bool m_quit;

		//! A flag to know if the alt key is beign pressed.
		bool m_altPressed;

		bool m_renderDebug;
	};
}