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

		virtual void update(float _deltaTime) = 0;
		virtual void render() = 0;
		virtual void init() = 0;
		virtual void dispatchMessage(const InputMessage& _message) = 0;

		virtual void onEnterCollision(int _tag) = 0;

		int m_collisionID;
		int m_id;
	};
}