#include "DynamicBody.h"

namespace TDF
{
	DynamicBody::DynamicBody()
	{
		m_body = nullptr;
	}

	DynamicBody::~DynamicBody()
	{

	}

	void DynamicBody::init(const b2BodyDef & _bodyDef, String _world)
	{
		PhysicsWorld* world = TDF::Box2DManager::GetInstance().getWorld(_world);

		if (world)
		{
			m_body = world->createBody(&_bodyDef);
		}
		else
		{
			printf("failed to get world");
		}
	}

	void DynamicBody::addFixture(const b2FixtureDef& _fixtureDef)
	{
		if (m_body)
		{
			m_body->CreateFixture(&_fixtureDef);
		}
		else
		{
			printf("Dynamic body is null");
		}
	}

	void DynamicBody::setPosition(const Vector2D & _pos)
	{
		m_body->SetTransform(b2Vec2(_pos.x * WORLD_TO_PHYSICS, _pos.y * WORLD_TO_PHYSICS), 0);
	}

	Vector2D DynamicBody::getPosition()
	{
		Vector2D l;

		l.x = m_body->GetPosition().x;
		l.y = m_body->GetPosition().y;

		return l;
	}

	void DynamicBody::setLinearVelocity(const Vector2D & _pos)
	{
		b2Vec2 l;
		l.x = _pos.x;
		l.y = _pos.y;

		m_body->SetLinearVelocity(l);
	}

	Vector2D DynamicBody::getLinearVelocity()
	{
		Vector2D l;

		l.x = m_body->GetLinearVelocity().x;
		l.y = m_body->GetLinearVelocity().y;

		return l;
	}

	void DynamicBody::setUserData(void * _data)
	{
		m_body->SetUserData(_data);
	}

	void DynamicBody::setFixedRotation(bool _fixed)
	{
		m_body->SetFixedRotation(_fixed);
	}
}