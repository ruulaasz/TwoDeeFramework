#pragma once

#include "Box2DManager.h"

namespace TDF
{
	class ContactListener : public b2ContactListener
	{
	public:
		ContactListener();
		~ContactListener();

		// Called when two fixtures begin to touch
		virtual void BeginContact(b2Contact* contact);
	};
}