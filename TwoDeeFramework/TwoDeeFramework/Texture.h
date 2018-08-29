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
		\param _path a string with the file path.
		*/
		virtual void load(std::string _path);

		//! A virtual function used to free the texture memory.
		virtual void free();

		//! Returns the texture width.
		/*!
		\sa getHeight()
		*/
		int getWidth() { return m_width; };

		//! Returns the texture height.
		/*!
		\sa getWidth()
		*/
		int getHeight() { return m_height; };

		//! Render the texture in a given position.
		/*!
		\param _x an integer for the X position.
		\param _y an integer for the Y position.
		*/
		void render(int _x, int _y, float _angle = 0);

		//! Set this texture alpha.
		/*!
		\param _a an integer for the new alpha.
		*/
		void setAlpha(int _a);

	public:
		//! A SDL 2.0 texture.
		SDL_Texture* m_sdlTexture;

		//! The width of the texture.
		int m_width;

		//! The height of the texture.
		int m_height;
	};
}