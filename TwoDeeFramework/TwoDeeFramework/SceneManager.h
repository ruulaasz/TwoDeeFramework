#pragma once

#include "Module.h"
#include "Actor.h"
#include "Scene.h"

namespace TDF
{
	//!  A manager class for Scenes.
	class SceneManager : public Module<SceneManager>
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		SceneManager();

		//! Default destructor.
		~SceneManager();

		//! Search an actor by id.
		/*!
		\param _id, the actor id.
		\return Actor*, a pointer to the founded actor.
		*/
		Actor* getActor(int _id);

		//! Set the active world
		/*!
		\param _world, a pointer to the world.
		*/
		void setActiveScene(string _scene);

		//! Get the current ID for the next created actor.
		int getID();

	public:
		//! The current runing scene.
		Scene* m_activeScene;

		//! A map with all loaded scenes.
		UnorderedMap<string, Scene*> m_allScenes;

	private:
		//! The current id.
		int m_currentID;
	};
}