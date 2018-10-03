#pragma once

#include "Box2DManager.h"

namespace TDF
{
	class DinamicBody
	{
	public:
		DinamicBody();
		~DinamicBody();

		void init(const b2BodyDef& _bodyDef, String _world);
		void addFixture(const b2FixtureDef& _fixtureDef);

		b2Body* m_dynamicBody;
	};
}