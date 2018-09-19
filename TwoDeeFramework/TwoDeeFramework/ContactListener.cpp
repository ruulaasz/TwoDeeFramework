#include "ContactListener.h"
#include "Actor.h"

namespace TDF
{
	ContactListener::ContactListener()
	{

	}

	ContactListener::~ContactListener()
	{

	}

	void ContactListener::BeginContact(b2Contact * contact)
	{
		int id = 0;

		void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserData)
		{
			id = static_cast<Actor*>(bodyUserData)->m_collisionID;
		}
			
		bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();

		if (bodyUserData)
		{
			static_cast<Actor*>(bodyUserData)->onEnterCollision(id);
		}
	}
}