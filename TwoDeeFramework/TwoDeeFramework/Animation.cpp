#include "Animation.h"
#include "rapidxml.hpp"
#include "StringTools.h"
#include "RenderManager.h"

namespace TDF
{
	Animation::Animation()
	{
		m_animSpeed = 0.15f;
		m_atlas = Shared_Ptr<Texture>(new Texture());
		m_currentFrame = 0;
		m_frameCount = 0;
		m_looped = false;
		m_playing = false;
	}

	Animation::~Animation()
	{
		
	}

	void Animation::loadFromFile(String _path)
	{
		rapidxml::xml_document<> doc;
		rapidxml::xml_node<> * root_node;

		//open the file
		ifstream theFile(_path);

		//dump the info into a buffer
		String buffer((istreambuf_iterator<char>(theFile)), 
					   istreambuf_iterator<char>());

		doc.parse<0>(&buffer[0]);

		//Find our root node
		root_node = doc.first_node("TextureAtlas");

		//load the atlas
		String imgPath = _path;

		size_t i = imgPath.length();
		--i;
		for (i; i >= 0; --i)
		{
			if (imgPath.at(i) == '\\')
			{
				break;
			}

			imgPath.pop_back();
		}

		imgPath += root_node->first_attribute("imagePath")->value();

		m_atlas->loadFromFile(imgPath);

		//read and copy the each frame data.
		for (rapidxml::xml_node<> * sprite_node = root_node->first_node("sprite"); 
			 sprite_node; 
			 sprite_node = sprite_node->next_sibling())
		{
			Sprite s;

			s.m_position.x = static_cast<float>(atof(sprite_node->first_attribute("x")->value()));
			s.m_position.y = static_cast<float>(atof(sprite_node->first_attribute("y")->value()));

			s.m_dimentions.x = static_cast<float>(atof(sprite_node->first_attribute("w")->value()));
			s.m_dimentions.y = static_cast<float>(atof(sprite_node->first_attribute("h")->value()));
			
			m_sprites.push_back(s);
		}

		m_frameCount = static_cast<int>(m_sprites.size());
	}

	void Animation::free()
	{
		m_atlas->free();
	}

	void Animation::play(bool _loop)
	{
		m_playing = true;
		m_looped = _loop;
		m_keyframeTime.start();
		m_currentFrame = 0;
	}

	void Animation::pause()
	{
		m_playing = false;
		m_keyframeTime.pause();
	}

	void Animation::resume()
	{
		m_playing = true;
		m_keyframeTime.resume();
	}

	void Animation::stop()
	{
		m_playing = false;
		m_looped = false;
		m_currentFrame = 0;
		m_keyframeTime.stop();
	}

	void Animation::update()
	{
		if (m_playing)
		{
			if (m_keyframeTime.getSeconds() >= m_animSpeed)
			{
				m_currentFrame++;
				m_keyframeTime.start();
			}

			if (m_currentFrame >= m_frameCount)
			{
				if (m_looped)
				{
					m_currentFrame = 0;
				}
				else
				{
					stop();
				}
			}
		}
	}

	Sprite Animation::getCurrentSprite()
	{
		if (m_atlas)
		{
			return m_sprites.at(m_currentFrame);
		}

		return Sprite();
	}

	Sprite Animation::getSprite(int _index)
	{
		if (_index >= m_sprites.size())
		{
			return m_sprites.back();
		}
		else if (_index >= 0)
		{
			return m_sprites.at(_index);
		}

		return Sprite();
	}
}