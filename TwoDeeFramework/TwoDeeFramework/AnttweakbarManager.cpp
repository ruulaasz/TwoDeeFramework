#include "AnttweakbarManager.h"
#include "SDL_Manager.h"
#include "ResourceManager.h"

namespace TDF
{
	bool m_hideGUI = false;

	AnttweakbarManager::AnttweakbarManager()
	{
		m_handled = 0;
		m_barCount = 0;

		m_antwBar = nullptr;
		m_sdlBar = nullptr;
		m_rscBar = nullptr;
		m_guiBar = nullptr;
	}

	AnttweakbarManager::~AnttweakbarManager()
	{

	}

	void TW_CALL resizeWindow(void *)
	{
		SDL_Manager::GetInstance().resizeWindow(SDL_Manager::GetInstance().m_windowWidth, SDL_Manager::GetInstance().m_windowHeight);
		TwWindowSize(SDL_Manager::GetInstance().m_windowWidth, SDL_Manager::GetInstance().m_windowWidth);
	}

	void TW_CALL hideGUI(void *)
	{
		m_hideGUI ^= 1;

		std::string name;
		if (m_hideGUI)
		{
			for (size_t i = 2; i < TwGetBarCount(); i++)
			{
				name = TwGetBarName(TwGetBarByIndex(i));
				name = name + " visible=false";
				TwDefine(name.c_str());
			}
		}
		else
		{
			for (size_t i = 2; i < TwGetBarCount(); i++)
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

		std::string name;
		if (m_hideGUI)
		{
			for (size_t i = 2; i < 5; i++)
			{
				name = TwGetBarName(TwGetBarByIndex(i));
				name = name + " visible=false";
				TwDefine(name.c_str());
			}
		}
		else
		{
			for (size_t i = 2; i < 5; i++)
			{
				name = TwGetBarName(TwGetBarByIndex(i));
				name = name + " visible=true";
				TwDefine(name.c_str());
			}
		}
	}

	void AnttweakbarManager::init()
	{
		TwInit(TW_DIRECT3D9, SDL_RenderGetD3D9Device(SDL_Manager::GetInstance().m_renderer));
		TwWindowSize(SDL_Manager::GetInstance().m_windowWidth, SDL_Manager::GetInstance().m_windowHeight);

		AntTweakBarInfo info;
		info.size = " size='200 5' ";
		info.position = " position='800 0' ";
		m_guiBar = createCustomBar(TEXT("Hide_GUI"), info);
		TwAddButton(m_guiBar, TEXT("Toggle all GUI"), hideGUI, NULL, TEXT(" label='Toggle all GUI' "));
		TwAddButton(m_guiBar, TEXT("Toggle framework GUI"), hideFGUI, NULL, TEXT(" label='Toggle framework GUI' "));

		info.size = " size='250 70' ";
		info.position = " position='0 0' ";
		m_antwBar = createCustomBar(TEXT("AntTweakBar_Info"), info);
		TwAddVarRO(m_antwBar, TEXT("Reading input:"), TW_TYPE_INT32, &m_handled, TEXT(" label='Reading Input:' "));
		TwAddVarRO(m_antwBar, TEXT("Number of Bars:"), TW_TYPE_INT32, &m_barCount, TEXT(" label='Number of Bars:' "));

		info.size = " size='250 160' ";
		info.position = " position='1800 0' ";
		m_sdlBar = createCustomBar(TEXT("SDLManager_Info"), info);
		TwAddVarRW(m_sdlBar, TEXT("Window width:"), TW_TYPE_INT32, &SDL_Manager::GetInstance().m_windowWidth, TEXT(" group=Window label='Window width:' min=100 max=1920 "));
		TwAddVarRW(m_sdlBar, TEXT("Window height:"), TW_TYPE_INT32, &SDL_Manager::GetInstance().m_windowHeight, TEXT(" group=Window label='Window height:' min=300 max=1080 "));
		TwAddButton(m_sdlBar, TEXT("Resize window"), resizeWindow, NULL, TEXT(" group=Window label='Resize window:' "));
		TwAddVarRO(m_sdlBar, TEXT("Fullscreen:"), TW_TYPE_INT32, &SDL_Manager::GetInstance().m_fullscreen, TEXT(" group=Window label='Fullscreen:' "));

		TwAddVarRO(m_sdlBar, TEXT("Mouse posX:"), TW_TYPE_INT32, &SDL_Manager::GetInstance().m_mousePosX, TEXT(" group=Mouse label='Mouse posX:' "));
		TwAddVarRO(m_sdlBar, TEXT("Mouse posY:"), TW_TYPE_INT32, &SDL_Manager::GetInstance().m_mousePosY, TEXT(" group=Mouse label='Mouse posY:' "));

		info.size = " size='250 90' ";
		info.position = " position='0 72' ";
		m_rscBar = createCustomBar(TEXT("ResourceManager_Info"), info);
		TwAddVarRO(m_rscBar, TEXT("Loaded:"), TW_TYPE_INT32, &ResourceManager::GetInstance().m_resourceCount, TEXT(" label='Loaded:' "));
		TwAddVarRO(m_rscBar, TEXT("Clean timer:"), TW_TYPE_FLOAT, &ResourceManager::GetInstance().m_currentTime, TEXT(" label='Clean timer:' precision=3 "));
		TwAddVarRW(m_rscBar, TEXT("Clean timelimit:"), TW_TYPE_FLOAT, &ResourceManager::GetInstance().m_timeLimit, TEXT(" label='Clean time limit:' precision=1 "));

		TwDefine(" GLOBAL contained=true ");
		TwDefine(" TW_HELP visible=false ");
	}

	TwBar * AnttweakbarManager::createDefaultBar(const char *_barName)
	{
		TwBar* newBar = TwNewBar(TEXT(_barName));

		std::string s = _barName;
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

		std::string s = _barName;
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

	void AnttweakbarManager::release()
	{
		TwTerminate();
	}
}
