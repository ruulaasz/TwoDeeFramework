#include "StaticBody.h"

namespace TDF
{
	StaticBody::StaticBody()
	{
		m_body = nullptr;
	}

	StaticBody::~StaticBody()
	{

	}

	void TDF::StaticBody::init(const b2BodyDef & _bodyDef, String _world)
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

	void TDF::StaticBody::addFixture(const b2FixtureDef & _fixtureDef)
	{
		if (m_body)
		{
			m_body->CreateFixture(&_fixtureDef);
		}
		else
		{
			printf("Static body is null");
		}
	}
}