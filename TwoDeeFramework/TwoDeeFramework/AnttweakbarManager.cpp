#include "AnttweakbarManager.h"
#include "SDL_Manager.h"
#include "StdHeaders.h"
#include "CameraManager.h"
#include "SystemManager.h"

#define DEFAULT_BARS 2
#define GUI_BARS 3

namespace TDF
{
	bool m_hideGUI = false;

	AnttweakbarManager::AnttweakbarManager()
	{
		m_handled = 0;

		m_sdlBar = nullptr;
		m_guiBar = nullptr;
		m_cameraBar = nullptr;
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
		info.size = " size='300 100' ";
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

		TwAddVarRW(m_guiBar,
			TEXT("render Debug:"),
			TW_TYPE_BOOL32,
			&SystemManager::GetInstance().m_renderDebug,
			TEXT(" group=Render label='render debug:' "));

		//SDLmanager bar
		info.size = " size='280 260' ";
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
				   TEXT("Mouse Screen PosX:"), 
				   TW_TYPE_INT32, 
				   &SDL_Manager::GetInstance().m_mousePosX, 
				   TEXT(" group=Mouse label='Mouse Screen posX:' "));

		TwAddVarRO(m_sdlBar, 
				   TEXT("Mouse Screen PosY:"), 
				   TW_TYPE_INT32, 
				   &SDL_Manager::GetInstance().m_mousePosY, 
				   TEXT(" group=Mouse label='Mouse Screen posY:' "));

		TwAddVarRO(m_sdlBar,
			TEXT("Mouse World posX:"),
			TW_TYPE_INT32,
			&SDL_Manager::GetInstance().m_mouseWorldPosX,
			TEXT(" group=Mouse label='Mouse World posX:' "));

		TwAddVarRO(m_sdlBar,
			TEXT("Mouse World posY:"),
			TW_TYPE_INT32,
			&SDL_Manager::GetInstance().m_mouseWorldPosY,
			TEXT(" group=Mouse label='Mouse World posY:' "));

		//Cameramanager bar
		info.size = " size='250 160' ";
		info.position = " position='0 0' ";
		m_cameraBar = createCustomBar(TEXT("Camera_Info"), info);

		TwAddVarRO(m_cameraBar,
			TEXT("Camera width:"),
			TW_TYPE_FLOAT,
			&CameraManager::GetInstance().m_camera.m_areaBox.m_width,
			TEXT(" group=Camera label='Camera width:' "));

		TwAddVarRO(m_cameraBar,
			TEXT("Camera height:"),
			TW_TYPE_FLOAT,
			&CameraManager::GetInstance().m_camera.m_areaBox.m_height,
			TEXT(" group=Camera label='Camera height:' "));

		TwAddVarRO(m_cameraBar,
			TEXT("Camera posX:"),
			TW_TYPE_FLOAT,
			&CameraManager::GetInstance().m_camera.m_areaBox.m_position.x,
			TEXT(" group=Camera label='Camera posX:' "));

		TwAddVarRO(m_cameraBar,
			TEXT("Camera posY:"),
			TW_TYPE_FLOAT,
			&CameraManager::GetInstance().m_camera.m_areaBox.m_position.y,
			TEXT(" group=Camera label='Camera posY:' "));

		TwAddVarRO(m_cameraBar,
			TEXT("Actors on camera:"),
			TW_TYPE_INT32,
			&CameraManager::GetInstance().m_actorsOnScreen,
			TEXT(" group=World label='Actors on camera:' "));
		
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