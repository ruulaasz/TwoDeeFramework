#pragma once

#include "StdHeaders.h"
#include "Module.h"
#include "Resource.h"
#include "StringTools.h"

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

		//! a template function, loads a resource from a file.
		/*!
		\param _path the path of the file.
		\return the loaded resource.
		*/
		template <class T>
		Shared_Ptr<T> loadFromFile(string _path)
		{
			//check if the path is not empty.
			if (_path.empty())
			{
				///ERROR: direccion vacia o invalida
				return nullptr;
			}

			//get the name of the resource.
			string path = "..\\resources\\" + _path;

			//search if the resource is already loaded.
			Shared_Ptr<T> newResource = searchInLoaded<T>(path);

			//If the resource does not exist.
			if (!newResource)
			{
				//Load it
				newResource = Shared_Ptr<T>(new T());
				newResource->loadFromFile(path);

				if (!newResource)
				{
					///ERROR: no se pudo cargar el archivo
					return nullptr;
				}
			}

			m_allResources[path] = newResource;

			return newResource;
		}

		//! a template function, creates an empty resource.
		/*!
		\param _name the name of the resource.
		\return the created resource.
		*/
		template <class T>
		T* createEmpty(string _name)
		{
			T* newResource = newResource = new T();
			newResource->setName(_name);
			return reinterpret_cast<T*>(newResource);
		}

		//! a template function, search for a resource.
		/*!
		\param _name the name of the resource.
		\return the found resource.
		*/
		template <class T>
		Shared_Ptr<T> searchInLoaded(string _name)
		{
			auto it = m_allResources.find(_name);

			if (it != m_allResources.end())
			{
				if (it->second)
				{
					return dynamic_pointer_cast<T>(it->second);
				}
				else
				{
					return nullptr;
				}
			}
			else
			{
				return nullptr;
			}
		}

		void printDebug()
		{
			printf("\n");

			for (auto resource : m_allResources)
			{
				printf("%s", resource.first.c_str());
				printf("\nNumber of References: %d\n\n", resource.second.use_count() - 1);
			}
		}

	public:
		//! An unordered map containing a resource and its name.
		UnorderedMap<string, Shared_Ptr<Resource>> m_allResources;
	};
}