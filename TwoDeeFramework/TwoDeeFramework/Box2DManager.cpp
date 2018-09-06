#include "Box2DManager.h"

namespace TDF
{
	Box2DManager::Box2DManager()
	{

	}

	Box2DManager::~Box2DManager()
	{

	}

	b2World * Box2DManager::createWorld(const Vector2D & _gravity)
	{
		b2Vec2 gravity(_gravity.x, _gravity.y); 
		b2World* world = new b2World(gravity);

		world->SetAllowSleeping(true);
		m_draw.SetFlags(b2Draw::e_shapeBit);
		world->SetDebugDraw(&m_draw);

		return world;
	}

	void Box2DManager::init()
	{
		m_allWorlds["earth"] = createWorld();
		m_allWorlds["moon"] = createWorld(Vector2D(0.0f, 18.5f));
		m_allWorlds["mars"] = createWorld(Vector2D(0.0f, 3.71f));
	}
}