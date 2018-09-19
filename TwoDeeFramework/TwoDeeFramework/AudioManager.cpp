#include "AudioManager.h"
#include "Sfx.h"

namespace TDF
{
	AudioManager::AudioManager()
	{

	}

	AudioManager::~AudioManager()
	{

	}

	void AudioManager::init()
	{
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

		Mix_AllocateChannels(100);
	}

	void AudioManager::release()
	{
		Mix_CloseAudio();
		Mix_Quit();
	}

	void AudioManager::setSfxVolume(Sfx * _sfx, int _volume)
	{
		Mix_VolumeChunk(_sfx->m_chunk, _volume);
	}

	void AudioManager::stopChannel(int _channel)
	{
		Mix_HaltChannel(_channel);
	}

	void AudioManager::stopChannelFadeOut(int _channel, int _ms)
	{
		Mix_FadeOutChannel(_channel, _ms);
	}

	void AudioManager::pauseChannel(int _channel)
	{
		Mix_Pause(_channel);
	}

	void AudioManager::resumeChannel(int _channel)
	{
		Mix_Resume(_channel);
	}

	bool AudioManager::isSfxPaused(int _channel)
	{
		return Mix_Paused(_channel);
	}

	bool AudioManager::isSfxPlaying(int _channel)
	{
		return Mix_Playing(_channel);
	}

	int AudioManager::setMusicVolume(int _volume)
	{
		return Mix_VolumeMusic(_volume);
	}

	void AudioManager::stopMusic()
	{
		Mix_HaltMusic();
	}

	void AudioManager::stopMusicFadeOut(int _ms)
	{
		Mix_FadeOutMusic(_ms);
	}

	void AudioManager::pauseMusic()
	{
		Mix_PauseMusic();
	}

	void AudioManager::ResumeMusic()
	{
		Mix_ResumeMusic();
	}

	bool AudioManager::isMusicPaused()
	{
		return Mix_PausedMusic();
	}
}