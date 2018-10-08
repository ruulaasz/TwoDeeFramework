#pragma once

#include "StdHeaders.h"
#include <Box2D.h>

namespace TDF
{
	//Forward declarations
	class DynamicBody;
	class StaticBody;

	//!  A physics world
	class PhysicsWorld
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		PhysicsWorld();

		//! Secondary constructor.
		/*!
		\param _world a pointer to a box2d world.
		*/
		PhysicsWorld(b2World* _world);

		//! Default destructor.
		~PhysicsWorld();

		//! Update the world.
		void update();

		//! Render the world.
		void render();

		//! Destroy a body of the world
		/*!
		\param _body a pointer to a dynamic body.
		*/
		void destroyBody(DynamicBody* _body);

		//! Destroy a body of the world
		/*!
		\param _body a pointer to a static body.
		*/
		void destroyBody(StaticBody* _body);

		//! Create a new body in the world.
		/*!
		\param _def the definition of the body.
		\return the created body.
		*/
		b2Body* createBody(const b2BodyDef* _def);

		//! The physics of the world.
		b2World* m_world;

		//! The name of the world.
		String m_name;

	private:
		//! The length of time passed to simulate (seconds).
		float32 m_timeStep;

		//! How strongly to correct velocity.
		int32 m_velocityIterations;

		//! How strongly to correct position.
		int32 m_positionIterations;
	};
}