#include "Background.h"
#include "RenderManager.h"

namespace TDF
{
	Background::Background()
	{

	}

	Background::~Background()
	{

	}

	void Background::init(Vector2D _pos, Vector2D _dimentions)
	{
		m_worldPosition = _pos;
		m_dimentions = _dimentions;

		m_boundingBox.m_position = m_worldPosition;
		m_boundingBox.m_width = m_dimentions.x;
		m_boundingBox.m_height = m_dimentions.y;
	}

	void Background::render()
	{
		if (m_texture)
		{
			SDL_Rect quadSrc = { 0, 0, m_texture.get()->m_width, m_texture.get()->m_height };
			SDL_Rect quadDst = { m_screenPosition.x , m_screenPosition.y , m_dimentions.x, m_dimentions.y };

			RenderManager::GetInstance().renderTextureEx(m_texture, quadSrc, quadDst);
		}

		AABB renderBox = m_boundingBox;
		renderBox.m_position = m_screenPosition;

		RenderManager::GetInstance().renderBox(renderBox);
	}
}