#include "Sfx.h"

namespace TDF
{
	Sfx::Sfx()
	{
		m_chunk = nullptr;
		m_currentChannel = 0;
	}

	Sfx::~Sfx()
	{

	}

	void Sfx::loadFromFile(std::string _path)
	{
		m_chunk = Mix_LoadWAV(_path.c_str());
	}

	void Sfx::free()
	{
		Mix_FreeChunk(m_chunk);
	}

	void Sfx::play(int _channel, int _loops)
	{
		m_currentChannel = Mix_PlayChannel(_channel, m_chunk, _loops);
	}

	void Sfx::playFadeIn(int _channel, int _ms, int _loops)
	{
		m_currentChannel = Mix_FadeInChannel(_channel, m_chunk, _loops, _ms);
	}
}