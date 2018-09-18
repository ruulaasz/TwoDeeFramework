#include "TextButton.h"
#include "RenderManager.h"

namespace TDF
{
	TextButton::TextButton()
	{
		m_text = nullptr;
	}

	TextButton::~TextButton()
	{

	}

	void TextButton::render()
	{
		Button::render();

		if (m_text)
		{
			RenderManager::GetInstance().renderText(m_text, m_position.x, m_position.y);
		}
	}

	void TextButton::fitText()
	{
		if (m_text)
		{
			m_dimentions.y = m_text->m_texture.m_height;
			m_dimentions.x = m_text->m_texture.m_width;
		}
	}
}