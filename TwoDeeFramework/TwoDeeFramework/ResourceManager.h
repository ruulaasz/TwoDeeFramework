#pragma once

#include "Module.h"
#include "Resource.h"
#include <map>

namespace TDF
{
	//!  A manager class for Resources. 
	/*!
	Used to load and manage various types of resources.
	*/
	class ResourceManager : public Module<ResourceManager>
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		ResourceManager();

		//! Default destructor.
		~ResourceManager();

		//! Updates the manager.
		/*!
		\param _deltaTime a float, the change of time.
		*/
		void update(float _deltaTime);

		//! Loads a new resource of give you an already loaded resource.
		/*!
		\param _name a string, the name of the resource.
		\param _type the type of the resource.
		\sa search()
		*/
		Resource* load(std::string _name, ResourceType _type);

		//! Gives you the reference to a resource without adding a reference.
		/*!
		\param _name a string, the name of the resource.
		\param _type the type of the resource.
		\sa load()
		*/
		Resource* search(std::string _name, ResourceType _type);

	private:
		//! Delete the unreferenced resources every X time.
		void cleanResources();

	public:
		//! A map containing a resource and its name.
		std::map<std::string, Resource*> m_allResources;

		//! Every time this time pass the cleanResources() function will be called.
		float m_timeLimit;

		//! Time passed since last cleanup.
		float m_currentTime;

		//! The number of resources loaded.
		int m_resourceCount;
	};
}