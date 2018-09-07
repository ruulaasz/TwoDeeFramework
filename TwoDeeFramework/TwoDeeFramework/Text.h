#pragma once

#include "Resource.h"
#include "SDL_Manager.h"
#include "Texture.h"

namespace TDF
{
	class Text : public Resource
	{
	public:
		Text();
		~Text();

		//! A virtual function used to load the texture.
		/*!
		\param _path a string with the file path.
		*/
		virtual void loadFromFile(std::string _path);

		//! A virtual function used to free the texture memory.
		virtual void free();

		//Creates image from font string 
		void loadFromRenderedText( std::string textureText, SDL_Color textColor );

		void setStyle(int _style);

		void resizeText(int _size);

		//! A SDL 2.0 texture.
		Texture m_texture;

		TTF_Font* m_font;
	};
}