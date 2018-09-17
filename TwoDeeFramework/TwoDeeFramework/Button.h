#pragma once

#include "Actor.h"
#include "Vector2D.h"

namespace TDF
{
	class Button : public Actor
	{
	public:
		Button();
		~Button();

		//! Update the actor.
		/*!
		\param _deltaTime the change of time.
		*/
		virtual void update(float _deltaTime);

		//! Render the actor.
		virtual void render();

		//! Initialize the actor.
		virtual void init();

		//! Dispatch a recieved message.
		/*!
		\param _message the receieved message.
		*/
		virtual void dispatchMessage(const InputMessage& _message);

		//! Collision with something.
		/*!
		\param _tag the id of the collided object.
		*/
		virtual void onEnterCollision(int _tag) { _tag; };
	
	public:
		bool m_selected;
		bool m_pressed;

		Vector2D m_position;
		Vector2D m_dimentions;

		bool m_renderDebug;

	private:
		SDL_Rect m_rect;
	};
}