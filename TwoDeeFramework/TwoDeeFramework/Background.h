#pragma once

#include "Actor.h"
#include "StdHeaders.h"
#include "Texture.h"

namespace TDF
{
	class Background : public Actor
	{
	public:
		Background();
		~Background();

		void init(Vector2D _pos, Vector2D _dimentions);

		virtual void render();

		Shared_Ptr<Texture> m_texture;

		Vector2D m_dimentions;
	};
}