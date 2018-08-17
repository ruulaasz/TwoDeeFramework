#pragma once

#include "Resource.h"
#include "SDL_Manager.h"

namespace TDF
{
	//!  A SDL 2.0 texture class 
	class Texture : public Resource
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Texture();

		//! Default destructor.
		~Texture();

		//! A virtual function used to load the texture.
		/*!
		\param a string with the file path.
		*/
		virtual void load(std::string _path);

		//! A virtual function used to free the texture memory.
		virtual void free();

		//! Returns the texture width.
		int getWidth() { return m_width; };

		//! Returns the texture height.
		int getHeight() { return m_height; };

	public:
		//! A SDL 2.0 texture.
		SDL_Texture* m_sdlTexture;

		//! The width of the texture.
		int m_width;

		//! The height of the texture.
		int m_height;
	};
}