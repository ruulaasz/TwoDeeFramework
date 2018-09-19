#pragma once

#include "SDL_Manager.h"

namespace TDF
{
	//!  A RGBA color
	class Color
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Color();

		//! Secondaty constructor.
		/*!
		\param _r the red channel value.
		\param _g the green channel value.
		\param _b the blue channel value.
		\param _a the alpha channel value, 255 by default.
		*/
		Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a = SDL_ALPHA_OPAQUE);

		//! Default destructor.
		~Color();

		//! the red channel.
		Uint8 r;

		//! The green channel.
		Uint8 g;

		//! The blue channel.
		Uint8 b;

		//! The alpha channel.
		Uint8 a;
	};
}