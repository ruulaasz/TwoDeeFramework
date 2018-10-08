#pragma once

#include "Box2DManager.h"

namespace TDF
{
	//!  A static body component
	class StaticBody
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		StaticBody();

		//! Default destructor.
		~StaticBody();

		//! Initialize the body
		/*!
		\param _bodyDef, the definition of the body.
		\param _world, the name of the world this body will serve.
		*/
		void init(const b2BodyDef& _bodyDef, String _world);

		//! Add a fixture to the body
		/*!
		\param _fixtureDef, the definition of the fixture.
		*/
		void addFixture(const b2FixtureDef& _fixtureDef);

	public:
		//! a box2D body
		b2Body* m_body;
	};
}