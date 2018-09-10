#pragma once

#include "InputMessage.h"

namespace TDF
{
	//!  An Actor class.
	class Actor
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Actor();

		//! Default destructor.
		~Actor();

		//! Update the actor.
		/*!
		\param _deltaTime the change of time.
		*/
		virtual void update(float _deltaTime) = 0;

		//! Render the actor.
		virtual void render() = 0;

		//! Initialize the actor.
		virtual void init() = 0;

		//! Dispatch a recieved message.
		/*!
		\param _message the receieved message.
		*/
		virtual void dispatchMessage(const InputMessage& _message) = 0;

		//! Collision with something.
		/*!
		\param _tag the id of the collided object.
		*/
		virtual void onEnterCollision(int _tag) = 0;

	public:
		//! The collision type id.
		int m_collisionID;

		//! The actor id.
		int m_id;
	};
}