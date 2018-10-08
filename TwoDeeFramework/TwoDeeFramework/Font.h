#pragma once

#include "Resource.h"
#include "SDL_Manager.h"
#include "StdHeaders.h"

namespace TDF
{
	//!  A True Type Font
	class Font : public Resource
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Font();

		//! Default destructor.
		~Font();

		//! A virtual function used to load the Font.
		/*!
		\param _path a string with the file path.
		*/
		virtual void loadFromFile(string _path);

		//! A virtual function used to free the font memory.
		virtual void free();

	public:
		//! A SDL 2.0 font.
		TTF_Font* m_font;
	};
}