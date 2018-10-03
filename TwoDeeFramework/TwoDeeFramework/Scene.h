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
		virtual void init(String _worldName = "earth");

	public:
		//! The world of the scene.
		World m_world;
		Shared_Ptr<Texture> m_background[8];
		Shared_Ptr<Music> m_backgroundMusic;
	};
}