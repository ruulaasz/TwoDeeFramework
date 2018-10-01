#pragma once

#include "Actor.h"
#include "Vector2D.h"
#include "Sfx.h"
#include "StdHeaders.h"

namespace TDF
{
	//!  A base clase for a GUI button.
	class Button : public Actor
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Button();

		//! Default destructor.
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
		//! If the button is selected.
		bool m_selected;

		//! If the audio of selection already was played.
		bool m_audioPlayed;

		//! If the button was pressed.
		bool m_pressed;

		//! If debug render will be active.
		bool m_renderDebug;
		
		//! The position of the button.
		Vector2D m_position;

		//! the dimentions of the button.
		Vector2D m_dimentions;

		//! The selection SFX.
		Shared_Ptr<Sfx> m_selectionSFX;

		//! The pressed SFX.
		Shared_Ptr<Sfx> m_activationSFX;

	private:
		//! The box of the button.
		SDL_Rect m_rect;
	};
}