#include "Box2DManager.h"

namespace TDF
{
	Box2DManager::Box2DManager()
	{

	}

	Box2DManager::~Box2DManager()
	{

	}

	PhysicsWorld * Box2DManager::createWorld(String _name, const Vector2D & _gravity)
	{
		b2Vec2 gravity(_gravity.x, _gravity.y); 
		b2World* world = new b2World(gravity);

		world->SetAllowSleeping(true);
		m_draw.SetFlags(b2Draw::e_shapeBit);
		world->SetDebugDraw(&m_draw);

		PhysicsWorld* w = new PhysicsWorld(world);
		w->m_name = _name;

		return w;
	}

	void Box2DManager::init()
	{
		m_allWorlds["earth"] = createWorld("earth");
		m_allWorlds["zeroG"] = createWorld("zeroG", Vector2D(0.0f, 0.0f));
	}

	PhysicsWorld* Box2DManager::getWorld(String _name)
	{
		auto it = m_allWorlds.find(_name);

		if (it != m_allWorlds.end())
		{
			if (it->second)
			{
				return it->second;
			}
			else
			{
				return m_allWorlds["earth"];
			}
		}
		else
		{
			return m_allWorlds["earth"];
		}
	}
}