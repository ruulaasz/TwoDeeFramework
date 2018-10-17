#pragma once

#include "Module.h"
#include "Camera2D.h"

namespace TDF
{
	class World;
	class Actor;

	class CameraManager : public Module<CameraManager>
	{
	public:
		CameraManager();
		~CameraManager();

		void checkWorld(World* _world);

		bool checkCollision(Actor* _actor);

		Camera2D m_camera;

		int m_actorsOnScreen;
	};
}