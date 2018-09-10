#pragma once

#include "SDL_Manager.h"

namespace TDF
{
	//!  A enum for a message types.
	enum messageType
	{
		CONTROLLER_INPUT=0,
		KEYBOARD_INPUT,
		MOUSE_INPUT,
		SYSTEM_INPUT,
		MAX_TYPE
	};

	//!  A data struct used to create a message. 
	struct inputData
	{
		SDL_Event event;
		void* data;
	};

	//!  An input message container class.
	class InputMessage
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		\sa Circle(Vector2D _center, float _radius);
		*/
		InputMessage();

		//! Default destructor.
		~InputMessage();

	public:
		//! The type of message.
		messageType m_type;

		//! The data of the message.
		inputData m_data;
	};
}