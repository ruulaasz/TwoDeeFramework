#pragma once

#include "World.h"
#include "Module.h"
#include "Actor.h"

namespace TDF
{
	class worldManager : public Module<worldManager>
	{
	public:
		worldManager();
		~worldManager();

		World* m_activeWorld;
		
		Actor* getActor(int _id);
		void setActiveWorld(World* _world);
	};
}