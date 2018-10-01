#pragma once

#include "Resource.h"
#include "SDL_Manager.h"
#include "Texture.h"
#include "Color.h"
#include "Font.h"

namespace TDF
{
	//!  A Text resource.
	class Text : public Resource
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Text();

		//! Default destructor.
		~Text();

		//! A virtual function used to load the Font.
		/*!
		\param _path a string with the file path.
		*/
		virtual void loadFromFile(string _path);

		//! A virtual function used to free the font memory.
		virtual void free() {};

		//! Change the text Style.
		void setStyle(int _style);

		//! Change the text Size.
		void resizeText(int _size);

		//! Set the text color.
		void setColor(Color _color);

		//! Set the text to display.
		void setText(string _text);

	private:
		//Creates image from font string. 
		void loadFromRenderedText(string textureText, SDL_Color textColor);

	public:
		//! A SDL 2.0 texture.
		Shared_Ptr<Texture> m_texture;

		//! A font.
		Shared_Ptr<Font> m_font;

		//! The color of the text.
		Color m_textColor;
		
		//! The text to display.
		string m_text;
	};
}