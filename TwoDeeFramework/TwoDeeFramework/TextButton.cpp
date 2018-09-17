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
			RenderManager::GetInstance().renderText(m_text, m_string, m_position.x, m_position.y);
		}
	}
}