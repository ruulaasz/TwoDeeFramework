#pragma once

#include "InputMessage.h"
#include "Vector2D.h"
#include "AABB.h"

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
		virtual void update(float _deltaTime) { _deltaTime; };

		//! Render the actor.
		virtual void render() {};

		//! Initialize the actor.
		virtual void init() {};

		//! Dispatch a recieved message.
		/*!
		\param _message the receieved message.
		*/
		virtual void dispatchMessage(const InputMessage& _message) { _message; };

		//! Collision with something.
		/*!
		\param _tag the id of the collided object.
		*/
		virtual void onEnterCollision(int _tag) { _tag; };

	public:
		//! The collision type id.
		int m_collisionID;

		//! The actor id.
		int m_id;

		//! The position in the world.
		Vector2D m_worldPosition;

		//! The position in the screen.
		Vector2D m_screenPosition;

		//! The bounding box of the actor.
		AABB m_boundingBox;

		bool m_rendereable;
	};
}