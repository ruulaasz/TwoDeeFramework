#include "Platform.h"
#include "RenderManager.h"

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

		m_dimentions.x = _dimentions.w * 2;
		m_dimentions.y = _dimentions.h * 2;
		
		polygonShape.SetAsBox(w, h, center, 0.0f);
		
		//create the fixture
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &polygonShape;
		myFixtureDef.density = 1;
		myFixtureDef.friction = 0.0f;

		m_body.m_body->CreateFixture(&myFixtureDef);

		m_worldPosition.x = static_cast<float>(_dimentions.x) - _dimentions.w;
		m_worldPosition.y = static_cast<float>(_dimentions.y) - _dimentions.h;

		m_boundingBox.m_position = m_worldPosition;
		m_boundingBox.m_width = m_dimentions.x;
		m_boundingBox.m_height = m_dimentions.y;
	}

	void Platform::render()
	{
		SDL_Rect quadSrc = { 0, 0, m_texture.get()->m_width, m_texture.get()->m_height };
		SDL_Rect quadDst = { m_screenPosition.x , m_screenPosition.y , m_dimentions.x, m_dimentions.y };

		RenderManager::GetInstance().renderTextureEx(m_texture, quadSrc, quadDst);

		TDF::AABB renderBox = m_boundingBox;
		renderBox.m_position = m_screenPosition;

		RenderManager::GetInstance().renderBox(renderBox);
	}
}