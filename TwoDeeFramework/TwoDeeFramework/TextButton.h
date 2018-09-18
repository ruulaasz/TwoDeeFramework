#pragma once

#include "Button.h"
#include "Text.h"

namespace TDF
{
	class TextButton : public Button
	{
	public:
		TextButton();
		~TextButton();

		void render();

		void fitText();

	public:
		Text* m_text;
	};
}