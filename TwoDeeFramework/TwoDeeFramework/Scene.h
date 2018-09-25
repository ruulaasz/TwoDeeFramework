#pragma once

#include "World.h"
#include "Music.h"

#define BACKGROUND_TEXTURES 8

namespace TDF
{
	//!  A Scene container.
	class Scene
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Scene();

		//! Default destructor.
		~Scene();

		//! Initialize the scene when changing to this scene.
		virtual void onEnter();

		//! Finalize the scene when changing to other scene.
		virtual void onExit();

		//! Updates the elements of the scene.
		/*!
		\param _deltaTime the change of time.
		*/
		virtual void update(float _deltaTime);

		//! Render the scene elements.
		virtual void render();

		//! Initialize the scene elements.
		virtual void init();

	public:
		//! The world of the scene.
		World m_world;
		Texture* m_background[8];
		Music* m_backgroundMusic;
	};
}