#pragma once

#include "Actor.h"
#include "StaticBody.h"
#include "StdHeaders.h"

namespace TDF
{
	class Texture;

	//!  A 2d platform
	class Platform : public Actor
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Platform();

		//! Default destructor.
		~Platform();

		//! Initialize the platform.
		/*!
		\param _world the world in witch this platform will function.
		\param _dimentions the dimentions of the platform.
		\param _path a string with the file path.
		*/
		void init(String _world, SDL_Rect _dimentions, int _collitionID);

		//! Render the platform.
		virtual void render();

	public:
		//! The body of the platform.
		StaticBody m_body;

		//! The dimentions of the platform.
		Vector2D m_dimentions;

		//! The texture of the platform.
		Shared_Ptr<Texture> m_texture;
	};
}