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
		virtual void loadFromFile(string _path);

		//! A virtual function used to free the texture memory.
		virtual void free();

		//! Creates the texture as a render target.
		void createAsRenderTarget();

		//! Changes the texture alpha channel.
		void setAlpha(Uint8 _a);

	public:
		//! A SDL 2.0 texture.
		SDL_Texture* m_sdlTexture;

		//! The width of the texture.
		int m_width;

		//! The height of the texture.
		int m_height;
	};
}