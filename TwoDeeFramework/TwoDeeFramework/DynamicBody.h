#pragma once

#include "Box2DManager.h"

namespace TDF
{
	//!  A Dynamic body component
	class DynamicBody
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		DynamicBody();

		//! Default destructor.
		~DynamicBody();

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

		//! Set the position of the body.
		/*!
		\param _pos, the new position.
		*/
		void setPosition(const Vector2D& _pos);

		//! Get the position of the body.
		/*!
		\return the position.
		*/
		Vector2D getPosition();

		//! Set the linear velocity of the body.
		/*!
		\param _vel, the new velocity.
		*/
		void setLinearVelocity(const Vector2D& _vel);

		//! Get the velocity of the body.
		/*!
		\return the velocity.
		*/
		Vector2D getLinearVelocity();

		//! Set the extra data for the body.
		/*!
		\param _data, the data.
		*/
		void setUserData(void* _data);

		//! Set if the body can rotate or not.
		/*!
		\param _fixed, if can rotate or not.
		*/
		void setFixedRotation(bool _fixed);

		//! a box2D body
		b2Body* m_body;
	};
}