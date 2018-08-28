#include "ResourceManager.h"
#include "Texture.h"

namespace TDF
{
	ResourceManager::ResourceManager()
	{
		m_currentTime = 0.0f;
		m_timeLimit = 10.0f;
		m_resourceCount = 0;
	}

	ResourceManager::~ResourceManager()
	{

	}

	Resource * ResourceManager::load(std::string _name, ResourceType _type)
	{
		std::string path = "..\\resources\\";
		Resource* newResource = search(_name, _type);

		if (!newResource)
		{
			switch (_type)
			{
			default:
				break;

			case RT_TEXTURE:
				newResource = new Texture();

				path += "textures\\";
				path += _name;
				path += ".png";

				reinterpret_cast<Texture*>(newResource)->load(path);
				newResource->m_type = RT_TEXTURE;
				m_allResources[_name] = newResource;
				m_resourceCount = m_allResources.size();
				break;
			}
		}

		newResource->addReference();
		return newResource;
	}

	Resource * ResourceManager::search(std::string _name, ResourceType _type)
	{
		std::map<std::string, Resource*>::iterator it;
		it = m_allResources.find(_name);

		if (it != m_allResources.end())
		{
			if (it->second->m_type == _type || _type == RT_DEFAULT)
			{
				return it->second;
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

	void ResourceManager::cleanResources()
	{
		for (std::map<std::string, Resource*>::const_iterator it = m_allResources.begin(); it != m_allResources.end(); ++it)
		{
			Resource* resource = it->second;

			if (resource)
			{
				if (resource->getReferenceCount() <= 0)
				{
					resource->free();
					m_allResources.erase(it);
					m_resourceCount = m_allResources.size();
					return;
				}
			}
		}
	}

	void ResourceManager::update(float _deltaTime)
	{
		m_currentTime += _deltaTime;

		if (m_currentTime >= m_timeLimit)
		{
			cleanResources();
			m_currentTime = 0.0f;
		}
	}
}