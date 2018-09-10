#pragma once

#include "Box2DManager.h"

namespace TDF
{
	//!  A handle for box2d collisions.
	class ContactListener : public b2ContactListener
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		ContactListener();

		//! Default destructor.
		~ContactListener();

		// Called when two fixtures begin to touch
		virtual void BeginContact(b2Contact* contact);
	};
}