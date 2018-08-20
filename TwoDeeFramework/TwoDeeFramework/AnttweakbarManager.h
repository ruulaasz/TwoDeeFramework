#pragma once

#pragma comment(lib, "AntTweakBar.lib")

#include "SDL_Manager.h"
#include <AntTweakBar.h>
#include "Resource.h"

namespace TDF
{
	class AnttweakbarManager : public Module<AnttweakbarManager>
	{
	public:
		AnttweakbarManager();
		~AnttweakbarManager();

		int m_handled;

		void init();
		TwBar* createBar(const char *_barName);
		void addBar(TwBar* _bar, const char *_name, ETwType _type, void* _var, const char *_label);
		void render();
		int handleEvent(const void *sdlEvent);
		void release();
	};
}