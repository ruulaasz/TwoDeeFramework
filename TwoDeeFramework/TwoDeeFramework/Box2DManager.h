#pragma once

#pragma comment(lib, "Box2D.lib")

#include "StdHeaders.h"
#include <Box2D.h>
#include "Module.h"
#include "Vector2D.h"
#include "Box2DDraw.h"

#define SCALE_TO_WORLD 0.01f
#define SCALE_TO_RENDER 100.0f

namespace TDF
{
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
		b2World* createWorld(const Vector2D& _gravity = Vector2D(0.0f, 9.8f));

		//! Initialize the default worlds.
		void init();

	private:
		//! The handle for debug rendering.
		Box2DDraw m_draw;

	public:
		//! A map with all created worlds.
		UnorderedMap<string, b2World*>m_allWorlds;
	};
}