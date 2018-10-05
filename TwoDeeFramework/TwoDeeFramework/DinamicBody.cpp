#include "DinamicBody.h"

namespace TDF
{
	DinamicBody::DinamicBody()
	{
		m_body = nullptr;
	}

	DinamicBody::~DinamicBody()
	{

	}

	void DinamicBody::init(const b2BodyDef & _bodyDef, String _world)
	{
		PhysicsWorld* world = TDF::Box2DManager::GetInstance().getWorld(_world);

		if (world)
		{
			m_body = world->m_world->CreateBody(&_bodyDef);
		}
		else
		{
			printf("failed to get world");
		}
	}

	void DinamicBody::addFixture(const b2FixtureDef& _fixtureDef)
	{
		if (m_body)
		{
			m_body->CreateFixture(&_fixtureDef);
		}
		else
		{
			printf("Dinamic body is null");
		}
	}
}