#pragma once

#pragma comment(lib, "Box2D.lib")

#include <unordered_map>
#include <Box2D.h>
#include "Module.h"
#include "Vector2D.h"
#include "Box2DDraw.h"

#define SCALE_TO_WORLD 0.01f
#define SCALE_TO_RENDER 100.0f

namespace TDF
{
	class Box2DManager : public Module<Box2DManager>
	{
	public:
		Box2DManager();
		~Box2DManager();

		b2World* createWorld(const Vector2D& _gravity = Vector2D(0.0f, 9.8f));

		Box2DDraw m_draw;

		void init();

		std::unordered_map<std::string, b2World*>m_allWorlds;
	};
}