#pragma once

#include <vector>
#include "Box2DManager.h"
#include "Actor.h"

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
		void init();

		//! Adds an actor to the world.
		void addActor(Actor* _actor);

	public:
		//! The actors in the world.
		std::vector<Actor*> m_allActors;

		//! The physiscs of the world.
		b2World* m_physicsWorld;

	private:
		//! The length of time passed to simulate (seconds).
		float32 m_timeStep;     

		//! How strongly to correct velocity.
		int32 m_velocityIterations; 

		//! How strongly to correct position.
		int32 m_positionIterations;   
	};
}