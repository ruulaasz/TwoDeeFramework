#pragma once

#include <memory>
#include <unordered_map>

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

		template <class T>
		T* loadFromFile(std::string _path)
		{
			if (_path.empty())
			{
				///ERROR: direccion vacia o invalida
				return nullptr;
			}

			std::string name = getNameFromPath(_path);

			T* newResource = searchInLoaded<T>(name);
				
			if (!newResource)
			{
				newResource = new T();
				newResource->loadFromFile(_path);
			}

			if (!newResource)
			{
				///ERROR: no se pudo cargar el archivo
				return nullptr;
			}

			m_allResources[name] = newResource;
			return reinterpret_cast<T*>(newResource);
		}

		template <class T>
		T* createEmpty(std::string _name)
		{
			T* newResource = newResource = new T();
			newResource->setName(_name);
			return reinterpret_cast<T*>(newResource);
		}

		template <class T>
		T* searchInLoaded(std::string _name)
		{
			auto it = m_allResources.find(_name);

			if (it != m_allResources.end())
			{
				if (dynamic_cast<T*>(it->second))
				{
					return reinterpret_cast<T*>(it->second);
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

	public:
		//! A map containing a resource and its name.
		std::unordered_map<std::string, Resource*> m_allResources;
	};
}