#include "TextButton.h"
#include "RenderManager.h"

namespace TDF
{
	TextButton::TextButton()
	{
		m_text = Shared_Ptr<Text>(new Text);
	}

	TextButton::~TextButton()
	{

	}

	void TextButton::render()
	{
		Button::render();

		if (m_text)
		{
			RenderManager::GetInstance().renderText(m_text, static_cast<int>(m_position.x), static_cast<int>(m_position.y));
		}
	}

	void TextButton::fitText()
	{
		if (m_text)
		{
			m_dimentions.y = static_cast<float>(m_text.get()->m_texture.get()->m_height);
			m_dimentions.x = static_cast<float>(m_text.get()->m_texture.get()->m_width);
		}
	}
}