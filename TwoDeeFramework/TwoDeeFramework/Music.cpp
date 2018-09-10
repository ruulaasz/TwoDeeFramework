#include "Music.h"

namespace TDF
{
	Music::Music()
	{
		m_music = nullptr;
	}

	Music::~Music()
	{
		
	}

	void TDF::Music::loadFromFile(std::string _path)
	{
		m_music = Mix_LoadMUS(_path.c_str());
	}

	void TDF::Music::free()
	{
		Mix_FreeMusic(m_music);
	}

	void Music::play(int _loops)
	{
		Mix_PlayMusic(m_music, _loops);
	}

	void Music::playFadeIn(int _ms, int _loops)
	{
		Mix_FadeInMusic(m_music, _loops, _ms);
	}
}