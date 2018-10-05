#include "Platform.h"

namespace TDF
{
	Platform::Platform()
	{
		m_alreadyInitialized = false;
	}

	Platform::~Platform()
	{

	}

	void Platform::init(String _world, SDL_Rect _dimentions, int _collitionID)
	{
		if (!m_alreadyInitialized)
		{
			b2BodyDef myBodyDef;
			myBodyDef.type = b2_staticBody;

			m_body.init(myBodyDef, _world);

			m_collisionID = _collitionID;
			m_body.m_staticBody->SetUserData(this);

			b2PolygonShape polygonShape;

			b2FixtureDef myFixtureDef;
			myFixtureDef.shape = &polygonShape;
			myFixtureDef.density = 1;
			myFixtureDef.friction = 0.0f;

			float w = _dimentions.w * WORLD_TO_PHYSICS;
			float h = _dimentions.h * WORLD_TO_PHYSICS;
			float x = _dimentions.x * WORLD_TO_PHYSICS;
			float y = _dimentions.y * WORLD_TO_PHYSICS;
			b2Vec2 center(x, y);

			m_worldPosition.x = _dimentions.x;
			m_worldPosition.y = _dimentions.y;

			polygonShape.SetAsBox(w, h, center, 0.0f);

			m_body.m_staticBody->CreateFixture(&myFixtureDef);

			m_alreadyInitialized = true;
		}
	}
}