#pragma once

#pragma comment(lib, "SDL2_mixer.lib")

#include <SDL_mixer.h>
#include "Module.h"

namespace TDF
{
	class Sfx;

	//!  A manager class for the Audio systems. 
	class AudioManager : public Module<AudioManager>
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		AudioManager();

		//! Default destructor.
		/*!
		Does nothing use the release() function instead.
		\sa release()
		*/
		~AudioManager();

		//! Initialize SDL_mixer subsystems.
		void init();

		//! Shut down the SDL 2.0 subsystems and cleans the memory.
		/*!
		\sa ~AudioManager()
		*/
		void release();

		//! Set the volume for a sfx sound.
		/*!
		\param _sfx the sound to modify.
		\param _volume the new volume.
		*/
		void setSfxVolume(Sfx*_sfx, int _volume);

		//! Stop the reproduction on a channel.
		/*!
		\param _channel the channel number, -1 for all channels.
		*/
		void stopChannel(int _channel);

		//! Stop the reproduction on a channel with a fade out.
		/*!
		\param _channel  the channel number, -1 for all channels.
		\param _ms the duration of the fade out.
		*/
		void stopChannelFadeOut(int _channel, int _ms);

		//! Pause the reproduction on a channel.
		/*!
		\param _channel the channel number, -1 for all channels.
		*/
		void pauseChannel(int _channel);

		//! Resume the reproduction on a channel.
		/*!
		\param _channel the channel number, -1 for all channels.
		*/
		void resumeChannel(int _channel);

		//! Get the pause status of a channel.
		/*!
		\param _channel  the channel number, -1 for all channels.
		\return if is paused or not.
		*/
		bool isSfxPaused(int _channel);

		//! Get if the channel is playing.
		/*!
		\param _channel the channel number, -1 for all channels.
		\return if is paused or not.
		*/
		bool isSfxPlaying(int _channel);

		//! Set the music volume.
		/*!
		\param _volume the new volume 0-128.
		\return if the recieved volume its -1 return the current volume.
		*/
		int setMusicVolume(int _volume);

		//! Stop the reproduction on the music.
		void stopMusic();

		//! Stop the reproduction on music with a fade out.
		/*!
		\param _ms the duration of the fade out.
		*/
		void stopMusicFadeOut(int _ms);

		//! Pause the reproduction on the music.
		void pauseMusic();

		//! Resume the reproduction on the music.
		void ResumeMusic();

		//! Get the pause status of the music.
		/*!
		\return if is paused or not.
		*/
		bool isMusicPaused();
	};
}