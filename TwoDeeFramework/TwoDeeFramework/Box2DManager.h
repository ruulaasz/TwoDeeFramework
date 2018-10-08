#pragma once

#pragma comment(lib, "Box2D.lib")

#include "StdHeaders.h"
#include <Box2D.h>
#include "Module.h"
#include "Vector2D.h"
#include "Box2DDraw.h"
#include "PhysicsWorld.h"

#define WORLD_TO_PHYSICS 0.01f
#define PHYSICS_TO_WORLD 100.0f

namespace TDF
{
	enum CollisionID
	{
		CI_PLATFORM = 1,
		CI_ENEMY
	};

	//!  A manager class for box2D library.
	class Box2DManager : public Module<Box2DManager>
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Box2DManager();

		//! Default destructor.
		~Box2DManager();

		//! Creates a new world.
		/*!
		\param _gravity, The worlds gravity.
		*/
		PhysicsWorld* createWorld(String _name, const Vector2D& _gravity = Vector2D(0.0f, 9.8f));

		//! Initialize the default worlds.
		void init();

		//! Creates a new world.
		/*!
		\param _name, The worlds name.
		\return a pointer to the world.
		*/
		PhysicsWorld* getWorld(String _name);

	private:
		//! The handle for debug rendering.
		Box2DDraw m_draw;

	public:
		//! A map with all created worlds.
		UnorderedMap<string, PhysicsWorld*> m_allWorlds;
	};
}