#pragma once

#include "World.h"

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
		virtual void onEnter() = 0;

		//! Finalize the scene when changing to other scene.
		virtual void onExit() = 0;

		//! Updates the elements of the scene.
		/*!
		\param _deltaTime the change of time.
		*/
		virtual void update(float _deltaTime) = 0;

		//! Render the scene elements.
		virtual void render() = 0;

	public:
		//! The world of the scene.
		World m_world;
	};
}