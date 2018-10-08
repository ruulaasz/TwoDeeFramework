#include "Platform.h"

namespace TDF
{
	Platform::Platform()
	{
		
	}

	Platform::~Platform()
	{

	}

	void Platform::init(String _world, SDL_Rect _dimentions, int _collitionID)
	{
		//create the body
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_staticBody;
		
		m_body.init(myBodyDef, _world);
		
		m_collisionID = _collitionID;
		m_body.m_body->SetUserData(this);
		
		//create the shape
		b2PolygonShape polygonShape;
		
		float w = _dimentions.w * WORLD_TO_PHYSICS;
		float h = _dimentions.h * WORLD_TO_PHYSICS;
		float x = _dimentions.x * WORLD_TO_PHYSICS;
		float y = _dimentions.y * WORLD_TO_PHYSICS;
		b2Vec2 center(x, y);
		
		polygonShape.SetAsBox(w, h, center, 0.0f);
		
		//create the fixture
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &polygonShape;
		myFixtureDef.density = 1;
		myFixtureDef.friction = 0.0f;

		m_body.m_body->CreateFixture(&myFixtureDef);

		m_worldPosition.x = _dimentions.x;
		m_worldPosition.y = _dimentions.y;
	}
}