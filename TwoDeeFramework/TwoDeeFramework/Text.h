#pragma once

#include "Resource.h"
#include "SDL_Manager.h"
#include "Texture.h"
#include "Color.h"

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
		virtual void loadFromFile(std::string _path);

		//! A virtual function used to free the font memory.
		virtual void free();

		//Creates image from font string. 
		void loadFromRenderedText(std::string textureText, SDL_Color textColor);

		//! Change the text Style.
		void setStyle(int _style);

		//! Change the text Size.
		void resizeText(int _size);

		void setColor(Color _color);

		void setText(std::string _text);

	public:
		//! A SDL 2.0 texture.
		Texture m_texture;

		//! A SDL 2.0 font.
		TTF_Font* m_font;

		Color m_textColor;
		
		std::string m_text;
	};
}