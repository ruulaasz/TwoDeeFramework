#pragma once

#include "Button.h"
#include "Text.h"

namespace TDF
{
	//!  A child class for a button containing text.
	class TextButton : public Button
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		TextButton();

		//! Default destructor.
		~TextButton();

		//! Render the button.
		void render();

		//! Set the dimentions of the button rect to match the size of the text.
		void fitText();

	public:
		//! The text to display.
		Shared_Ptr<Text> m_text;
	};
}