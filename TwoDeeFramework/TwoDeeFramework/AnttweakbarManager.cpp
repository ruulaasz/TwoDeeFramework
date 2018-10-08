#include "AnttweakbarManager.h"
#include "SDL_Manager.h"
#include "StdHeaders.h"

#define DEFAULT_BARS 2
#define GUI_BARS 2

namespace TDF
{
	bool m_hideGUI = false;

	AnttweakbarManager::AnttweakbarManager()
	{
		m_handled = 0;
		m_barCount = 0;

		m_sdlBar = nullptr;
		m_guiBar = nullptr;
	}

	AnttweakbarManager::~AnttweakbarManager()
	{

	}

	void TW_CALL hideGUI(void *)
	{
		m_hideGUI ^= 1;
		string name;

		if (m_hideGUI)
		{
			for (int i = DEFAULT_BARS; i < TwGetBarCount(); i++)
			{
				name = TwGetBarName(TwGetBarByIndex(i));
				name = name + " visible=false";
				TwDefine(name.c_str());
			}
		}
		else
		{
			for (int i = DEFAULT_BARS; i < TwGetBarCount(); i++)
			{
				name = TwGetBarName(TwGetBarByIndex(i));
				name = name + " visible=true";
				TwDefine(name.c_str());
			}
		}
	}

	void TW_CALL hideFGUI(void *)
	{
		m_hideGUI ^= 1;
		string name;

		if (m_hideGUI)
		{
			for (int i = DEFAULT_BARS; i <= GUI_BARS; i++)
			{
				name = TwGetBarName(TwGetBarByIndex(i));
				name = name + " visible=false";
				TwDefine(name.c_str());
			}
		}
		else
		{
			for (int i = DEFAULT_BARS; i <= GUI_BARS; i++)
			{
				name = TwGetBarName(TwGetBarByIndex(i));
				name = name + " visible=true";
				TwDefine(name.c_str());
			}
		}
	}

	void AnttweakbarManager::init()
	{
		//init library
		TwInit(TW_DIRECT3D9, SDL_RenderGetD3D9Device(SDL_Manager::GetInstance().m_renderer));

		TwWindowSize(SDL_Manager::GetInstance().m_windowWidth, 
					 SDL_Manager::GetInstance().m_windowHeight);

		//hide gui bar
		AntTweakBarInfo info;
		info.size = " size='200 5' ";
		info.position = " position='800 0' ";
		m_guiBar = createCustomBar(TEXT("Hide_GUI"), info);

		TwAddButton(m_guiBar, 
					TEXT("Toggle all GUI"), 
					hideGUI, 
					NULL, 
					TEXT(" label='Toggle all GUI' "));

		TwAddButton(m_guiBar, 
					TEXT("Toggle framework GUI"), 
					hideFGUI,
					NULL,
					TEXT(" label='Toggle framework GUI' "));

		//SDLmanager bar
		info.size = " size='250 160' ";
		info.position = " position='1800 0' ";
		m_sdlBar = createCustomBar(TEXT("SDLManager_Info"), info);

		TwAddVarRW(m_sdlBar, 
				   TEXT("Window width:"), 
				   TW_TYPE_INT32, 
				   &SDL_Manager::GetInstance().m_windowWidth, 
				   TEXT(" group=Window label='Window width:' min=100 max=1920 "));

		TwAddVarRW(m_sdlBar, 
				   TEXT("Window height:"), 
				   TW_TYPE_INT32, 
				   &SDL_Manager::GetInstance().m_windowHeight, 
				   TEXT(" group=Window label='Window height:' min=300 max=1080 "));

		TwAddVarRO(m_sdlBar, 
				   TEXT("Fullscreen:"), 
				   TW_TYPE_BOOL32, 
				   &SDL_Manager::GetInstance().m_fullscreen, 
				   TEXT(" group=Window label='Fullscreen:' "));

		TwAddVarRO(m_sdlBar, 
				   TEXT("Mouse posX:"), 
				   TW_TYPE_INT32, 
				   &SDL_Manager::GetInstance().m_mousePosX, 
				   TEXT(" group=Mouse label='Mouse posX:' "));

		TwAddVarRO(m_sdlBar, 
				   TEXT("Mouse posY:"), 
				   TW_TYPE_INT32, 
				   &SDL_Manager::GetInstance().m_mousePosY, 
				   TEXT(" group=Mouse label='Mouse posY:' "));
		
		TwDefine(" GLOBAL contained=true ");
		TwDefine(" TW_HELP visible=false ");
	}

	TwBar * AnttweakbarManager::createDefaultBar(const char *_barName)
	{
		TwBar* newBar = TwNewBar(TEXT(_barName));

		//default values
		string s = _barName;
		s += " color='255 128 255' alpha=180 ";
		TwDefine(s.c_str());

		s = _barName;
		s += " text=light  ";
		TwDefine(s.c_str());

		s = _barName;
		s += " position='0 0' ";
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

		m_barCount = TwGetBarCount();

		return  newBar;
	}

	TwBar * AnttweakbarManager::createCustomBar(const char * _barName, AntTweakBarInfo _info)
	{
		TwBar* newBar = TwNewBar(TEXT(_barName));

		string s = _barName;
		s += _info.color;
		TwDefine(s.c_str());

		s = _barName;
		s += _info.text;
		TwDefine(s.c_str());

		s = _barName;
		s += _info.position;
		TwDefine(s.c_str());

		s = _barName;
		s += _info.size;
		TwDefine(s.c_str());

		s = _barName;
		s += _info.valuesWidth;
		TwDefine(s.c_str());

		s = _barName;
		s += _info.refresh;
		TwDefine(s.c_str());

		m_barCount = TwGetBarCount();

		return  newBar;
	}

	void AnttweakbarManager::render()
	{
		TwDraw();
	}

	int AnttweakbarManager::handleEvent(const void * sdlEvent)
	{
		m_handled = TwEventSDL(sdlEvent, SDL_MAJOR_VERSION, SDL_MINOR_VERSION);

		return m_handled;
	}

	void AnttweakbarManager::updateWindowSize()
	{
		TwWindowSize(SDL_Manager::GetInstance().m_windowWidth, 
					 SDL_Manager::GetInstance().m_windowHeight);
	}

	void AnttweakbarManager::release()
	{
		TwTerminate();
	}

	void AnttweakbarManager::hideBars(bool _hide)
	{
		m_hideGUI = _hide;
		string name;

		if (m_hideGUI)
		{
			for (int i = DEFAULT_BARS; i < TwGetBarCount(); i++)
			{
				name = TwGetBarName(TwGetBarByIndex(i));
				name = name + " visible=false";
				TwDefine(name.c_str());
			}
		}
		else
		{
			for (int i = DEFAULT_BARS; i < TwGetBarCount(); i++)
			{
				name = TwGetBarName(TwGetBarByIndex(i));
				name = name + " visible=true";
				TwDefine(name.c_str());
			}
		}
	}
}