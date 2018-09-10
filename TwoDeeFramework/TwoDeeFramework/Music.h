#pragma once

#include <SDL_mixer.h>
#include "Resource.h"

namespace TDF
{
	//!  A music resource class.
	class Music : public Resource
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Music();

		//! Default destructor.
		~Music();
		
		//! A virtual function used to load the resource.
		/*!
		\param _path a string with the file path.
		*/
		virtual void loadFromFile(std::string _path);

		//! A virtual function used to free the resource memory.
		virtual void free();

		/**
		* Reproduce the sfx file
		*
		* @param _loops
		* the number of loops, -1 by default(infinite*)
		*
		*/
		void play(int _loops = -1);

		/**
		* Reproduce the sfx file with a fade in effect
		*
		* @param _ms
		* the time to reach max volume.
		*
		* @param _loops
		* the number of loops, -1 by default(infinite*)
		*
		*/
		void playFadeIn(int _ms, int _loops = -1);

	public:
		Mix_Music* m_music;
	};
}