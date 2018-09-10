#pragma once

#include "World.h"
#include "Module.h"
#include "Actor.h"

namespace TDF
{
	//!  A manager class for the created worlds. 
	class WorldManager : public Module<WorldManager>
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		WorldManager();

		//! Default destructor.
		~WorldManager();

		//! Search an actor by id.
		/*!
		\param _id, the actor id.
		\return Actor*, a pointer to the founded actor.
		*/
		Actor* getActor(int _id);

		//! Set the active world
		/*!
		\param _world, a pointer to the world.
		*/
		void setActiveWorld(World* _world);

	public:
		World* m_activeWorld;
	};
}