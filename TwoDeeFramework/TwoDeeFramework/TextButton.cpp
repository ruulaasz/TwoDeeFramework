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

	void TextButton::init(int _size, Color _color, String _text)
	{
		if (m_text)
		{
			m_text.get()->resizeText(_size);
			m_text.get()->setColor(_color);
			m_text.get()->setText(_text);
			fitText();
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