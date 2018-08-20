#include "AnttweakbarManager.h"
#include <windows.h>

namespace TDF
{
	AnttweakbarManager::AnttweakbarManager()
	{

	}

	AnttweakbarManager::~AnttweakbarManager()
	{

	}

	void AnttweakbarManager::init()
	{
		TwInit(TW_DIRECT3D9, SDL_RenderGetD3D9Device(SDL_Manager::GetInstance().m_renderer));
		TwWindowSize(SDL_Manager::GetInstance().m_windowWidth, SDL_Manager::GetInstance().m_windowWidth);
	}

	TwBar * AnttweakbarManager::createBar(const char *_barName)
	{
		TwBar* newBar = TwNewBar(TEXT(_barName));

		std::string s = _barName;
		s += " color='255 128 255' alpha=180 ";
		TwDefine(s.c_str());

		s = _barName;
		s += " text=light  ";
		TwDefine(s.c_str());

		s = _barName;
		s += " position='50 33' ";
		TwDefine(s.c_str());

		s = _barName;
		s += " size='250 290' ";
		TwDefine(s.c_str());

		s = _barName;
		s += " valueswidth=90 ";
		TwDefine(s.c_str());

		s = _barName;
		s += " refresh=0.01 ";
		TwDefine(s.c_str());

		TwDefine(" GLOBAL contained=true ");

		return  newBar;
	}

	void AnttweakbarManager::addBar(TwBar * _bar, const char * _name, ETwType _type, void * _var, const char * _label)
	{
		int *i;

		switch (_type)
		{
		default:
			break;
		case TW_TYPE_INT32:
			i = static_cast<int*>(_var);
			TwAddVarRO(_bar, _name, TW_TYPE_INT32, i, _label);
			break;
		}
	}

	void AnttweakbarManager::render()
	{
		TwDraw();
	}

	int AnttweakbarManager::handleEvent(const void * sdlEvent)
	{
		return TwEventSDL(sdlEvent, SDL_MAJOR_VERSION, SDL_MINOR_VERSION);
	}

	void AnttweakbarManager::release()
	{
		TwTerminate();
	}
}
