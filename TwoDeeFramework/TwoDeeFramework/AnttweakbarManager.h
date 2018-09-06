#pragma once

#pragma comment(lib, "AntTweakBar.lib")

#include <windows.h>
#include <AntTweakBar.h>
#include "Module.h"

namespace TDF
{
	//!  A data struct used to create a custom bar. 
	struct AntTweakBarInfo
	{
		const char* color = " color='0 0 255' alpha=120 ";
		const char* text = " text=light  ";
		const char* position = " position='0 0' ";
		const char* size = " size='250 290' ";
		const char* valuesWidth = " valueswidth=90 ";
		const char* refresh = " refresh=0.01 ";
	};

	//!  A manager class for AntTweakBar. 
	/*!
	Used to initialize and use the AntTweakBar modules.
	*/
	class AnttweakbarManager : public Module<AnttweakbarManager>
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		AnttweakbarManager();

		//! Default destructor.
		/*!
		Does nothing use the release() function instead.
		\sa release()
		*/
		~AnttweakbarManager();

		//! Initialize AntTweakBar subsystems.
		void init();

		//! Creates a new default Bar.
		/*!
		\param _barName a constant character pointer, the bar name.
		\sa addBar()
		*/
		TwBar* createDefaultBar(const char *_barName);

		//! Creates a new custom Bar.
		/*!
		\param _barName a constant character pointer, the bar name.
		\sa addBar()
		*/
		TwBar* createCustomBar(const char *_barName, AntTweakBarInfo _info);

		//! Renders the bars.
		void render();

		//! Handle the anttweakbar events.
		int handleEvent(const void *sdlEvent);

		//! Updates the manager values with the current window size.
		void updateWindowSize();

		//! Shut down the AntTweakBar subsystems and cleans the memory.
		/*!
		\sa ~AnttweakbarManager()
		*/
		void release();

		void hideBars(bool _hide);

	public:
		//! If the manager already handled any input.
		int m_handled;

		//! the number of created bars, the manager always starts with 1 bar.
		int m_barCount;

	private:
		//! A bar holding the antweakbar manager info.
		TwBar *m_antwBar;

		//! A bar holding the SDL manager info.
		TwBar *m_sdlBar;

		//! A bar holding the hide gui button.
		TwBar *m_guiBar;
	};
}