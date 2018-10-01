#pragma once

#include "StdHeaders.h"
#include "InputMessage.h"

namespace TDF
{
	//!  A manager class for input messaging.
	class InputManager : public Module<InputManager>
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		InputManager();

		//! Default destructor.
		~InputManager();

		//! Push a message to the queue.
		/*!
		\param _message the message.
		*/
		void queueMessage(const InputMessage& _message);

		//! Subscribe to recieve a type of message.
		/*!
		\param _type the message type.
		\param _id the subscriber id.
		*/
		void subscribe(messageType _type, int _id);

		//! Send the queue messages to the subscribers.
		void update();

		//! Send a message to an Actor.
		/*!
		\param _message the message.
		\param _id the subscriber id.
		*/
		void sendMessage(const InputMessage& _message, int _id);

		//! Get the sdl events.
		/*!
		\param _event the events container.
		*/
		void pollEvent(SDL_Event _event);

		//! Post a sdl event in the queue.
		/*!
		\param _event the events container.
		*/
		void pushEvent(SDL_Event _event);

	private:
		//! The messages to attend.
		Queue<InputMessage> m_messageQueue;

		//! A map of the subscribers.
		UnorderedMap<int, messageType> m_subscribers;

		//! A message to fill.
		InputMessage m_message;
	};
}