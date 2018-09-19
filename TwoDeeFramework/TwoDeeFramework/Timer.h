#pragma once

#include "SDL_Manager.h"

namespace TDF
{
	//!  A class to manage time.
	class Timer
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Timer();

		//! Default destructor.
		~Timer();

		//! Start the timer.
		void start();

		//! Stop the timer.
		void stop();

		//! Pause the timer.
		void pause();

		//! Resume the timer.
		void resume();

		//! Get the current time in ticks.
		Uint32 getTicks();

		//! Get the current time in seconds.
		float getSeconds();

		//! Get if the timer is running or not.
		/*!
		\return if the timer is runing.
		*/
		bool isStarted();

		//! Get if the timer is paused or not.
		/*!
		\return if the timer is paused.
		*/
		bool isPaused();

	private:
		//! The starting time.
		Uint32 m_startTicks;

		//! The time the timer was paused.
		Uint32 m_pausedTicks;

		//! If the timer is paused.
		bool m_paused;

		//! If the timer is running.
		bool m_started;
	};
}