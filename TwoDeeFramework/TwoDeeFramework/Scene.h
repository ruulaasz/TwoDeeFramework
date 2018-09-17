#pragma once

#include "World.h"

namespace TDF
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		virtual void onEnter() = 0;
		virtual void onExit() = 0;
		virtual void update(float _deltaTime) = 0;
		virtual void render() = 0;

	public:
		World m_world;
	};
}