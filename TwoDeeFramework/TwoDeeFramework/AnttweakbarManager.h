#pragma once

#pragma comment(lib, "AntTweakBar.lib")

#include "SDL_Manager.h"
#include <AntTweakBar.h>

namespace TDF
{
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

		//! Creates a new Bar.
		/*!
		\param _barName a constant character pointer, the bar name.
		\sa addBar()
		*/
		TwBar* createBar(const char *_barName);

		//! Add a new parameter to a Bar.
		/*!
		\param _bar a pointer to the Bar.
		\param _name a constant character pointer, the param name.
		\param _var a pointer to the info to display.
		\param _label a constant character pointer, the param name to display.
		\sa createBar()
		*/
		void addBar(TwBar* _bar, const char *_name, ETwType _type, void* _var, const char *_label);

		//! Renders the bars.
		void render();

		//! Handle the anttweakbar events.
		int handleEvent(const void *sdlEvent);

		//! Shut down the AntTweakBar subsystems and cleans the memory.
		/*!
		\sa ~AnttweakbarManager()
		*/
		void release();

	public:
		//! If the manager already handled any input.
		int m_handled;
	};
}