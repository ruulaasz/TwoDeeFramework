#pragma once

#include "Module.h"
#include "Actor.h"
#include "Scene.h"

namespace TDF
{
	class SceneManager : public Module<SceneManager>
	{
	public:
		SceneManager();
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
		void setActiveScene(Scene* _scene);

		int getID();

	public:
		Scene* m_activeScene;

	private:
		int m_currentID;
	};
}