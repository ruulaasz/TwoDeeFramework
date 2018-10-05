#pragma once

#include "Actor.h"
#include "StaticBody.h"

namespace TDF
{
	class Platform : public Actor
	{
	public:
		Platform();
		~Platform();

		void init(String _world, SDL_Rect _dimentions, int _collitionID);
	public:
		StaticBody m_body;
		Vector2D m_worldPosition;

	private:
		bool m_alreadyInitialized;
	};
}