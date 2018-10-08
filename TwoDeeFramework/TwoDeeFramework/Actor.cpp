#include "Actor.h"
#include "SceneManager.h"

namespace TDF
{
	Actor::Actor()
	{
		m_collisionID = 0;
		m_id = SceneManager::GetInstance().getID();
	}

	Actor::~Actor()
	{

	}
}