#pragma once

#include "Actor.h"
#include "PhysicsWorld.h"

namespace TDF
{
	//!  A world container class.
	class World
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		World();

		//! Default destructor.
		~World();

		//! Updates all the actors.
		/*!
		\param _deltaTime the change in time.
		*/
		void update(float _deltaTime);

		//! Render all the actors.
		void render();

		//! Initialize the world.
		void init(String _worldName = "earth");

		//! Adds an actor to the world.
		void addActor(Actor* _actor);

	public:
		//! The actors in the world.
		Vector<Actor*> m_allActors;

		//! The physics of the world.
		PhysicsWorld m_physics;
	};
}