#pragma once

#include <SDL_mixer.h>
#include "Resource.h"

namespace TDF 
{
	//!  A sfx resource class.
	class Sfx : public Resource
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Sfx();

		//! Default destructor.
		~Sfx();

		//! A virtual function used to load the resource.
		/*!
		\param _path a string with the file path.
		*/
		virtual void loadFromFile(string _path);

		//! A virtual function used to free the resource memory.
		virtual void free();

		//! Reproduce the sfx.
		/*!
		\param _channel the channel number.
		\param _loops the number of loops, 0 by default.
		*/
		void play(int _channel, int _loops = 0);

		//! Reproduce the sfx with a fade in effect.
		/*!
		\param _channel the channel number.
		\param _ms the time to reach max volume.
		\param _loops the number of loops, 0 by default.
		*/
		void playFadeIn(int _channel, int _ms, int _loops = 0);

	public:
		//! The audio chunk.
		Mix_Chunk* m_chunk;

		//! The current channel of this sfx.
		int m_currentChannel;
	};
}