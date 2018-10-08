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

		//! Updates the elements of the scene.
		/*!
		\param _size the size of the text.
		\param _color the color of the text.
		\param _text the text to show.
		*/
		void init(int _size, Color _color, String _text);

	public:
		//! The text to display.
		Shared_Ptr<Text> m_text;
	};
}