#pragma once

#include "Resource.h"
#include "Texture.h"
#include "Vector2D.h"
#include <vector>
#include "Timer.h"

namespace TDF
{
	struct Sprite
	{
		Vector2D m_atlasPos;
		Vector2D m_dimentions;
	};

	class Animation : public Resource
	{
	public:
		Animation();
		~Animation();

		//! A virtual function used to load the resource.
		/*!
		\param _path a string with the file path.
		*/
		virtual void loadFromFile(std::string _path);

		//! A virtual function used to free the resource memory.
		virtual void free();
		
		void play(bool _loop);
		void pause();
		void resume();
		void stop();
		void update();

		void setAlpha(int _alpha) { m_atlas->setAlpha(_alpha); };

	public:
		Texture* m_atlas;

		int m_frameNum;
		float m_animSpeed;
		int m_currentFrame;
		Timer m_keyframeTime;
		std::vector<Sprite> m_sprites;

		bool m_playing;
		bool m_looped;
	};
}