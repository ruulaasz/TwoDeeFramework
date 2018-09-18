#pragma once

#include "SDL_Manager.h"

namespace TDF
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		void start();
		void stop();
		void pause();
		void unPause();

		Uint32 getTicks();
		float getSeconds();

		bool isStarted();
		bool isPaused();

	private:
		Uint32 m_startTicks;
		Uint32 m_pausedTicks;

		bool m_paused;
		bool m_started;
	};
}