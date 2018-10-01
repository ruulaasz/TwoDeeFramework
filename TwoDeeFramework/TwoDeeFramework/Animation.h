#pragma once

#include "Texture.h"
#include "Timer.h"
#include "Vector2D.h"
#include "StdHeaders.h"

namespace TDF
{
	//! A structure to hold a sprite or keyframe data.
	struct Sprite
	{
		Vector2D m_position;
		Vector2D m_dimentions;
	};

	//!  An Animation class
	class Animation : public Resource
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Animation();

		//! Default destructor.
		~Animation();

		//! A virtual function used to load the resource.
		/*!
		\param _path a string with the file path.
		*/
		virtual void loadFromFile(string _path);

		//! A virtual function used to free the resource memory.
		virtual void free();
		
		//! Play the animation from the start
		/*!
		\param _loop to repeat the animation endlessly.
		*/
		void play(bool _loop = true);

		//! Pause the animation.
		void pause();

		//! Resume a paused animation.
		void resume();

		//! Stop an animation.
		void stop();

		//! Update the animation.
		void update();

		//! Set the alpha of the whole atlas.
		/*!
		\param _alpha the new alpha channel value.
		*/
		void setAlpha(Uint8 _alpha) { m_atlas->setAlpha(_alpha); };

		//! Get if the animation is playing or not.
		/*!
		\return if the animation is playing.
		*/
		bool isPlaying() { return m_playing; };

		//! Get the current keyframe information
		/*!
		\return A structure holding the current keyframe data.
		*/
		Sprite getCurrentSprite();

		//! Set the speed of the animation.
		/*!
		\param _speed the new animation speed value.
		*/
		void setAnimationSpeed(float _speed) { m_animSpeed = _speed; };

	public:
		//! The atlas holding all the frames.
		Shared_Ptr<Texture> m_atlas;

	private:
		//! If the animation is playing
		bool m_playing;

		//! If the animation will be looped.
		bool m_looped;

		//! The number of frames in the animation.
		int m_frameCount;

		//! The index of the current frame.
		int m_currentFrame;

		//! The speed of the animation.
		float m_animSpeed;

		//! A timer to change keyframe.
		Timer m_keyframeTime;

		//! A vector with all the frames data.
		Vector<Sprite> m_sprites;
	};
}