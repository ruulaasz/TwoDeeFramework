#include <cstdio>
#include <windows.h>	
#include <Box2D.h>
#include <TDF.h>
#include "DebugDraw.h"
#include "Player.h"

TDF::SDL_Manager* g_SDLManager;
TDF::ResourceManager* g_ResourceManager;
TDF::BoidManager* g_BoidManager;
TDF::RenderManager* g_RenderManager;

#ifdef _WIN64

#else
TDF::AnttweakbarManager* g_AnttweakbarManager;
#endif

Uint64 g_time = SDL_GetPerformanceCounter();
Uint64 g_lastTime = 0;
float g_deltaTime = 0.0f;

bool g_quit;
bool g_lAlt;
int g_guiHandled;

Player g_player;

b2Vec2 gravity(0.0f, 9.8f); //normal earth gravity, 9.8 m/s/s straight down!
b2World* myWorld = new b2World(gravity);
float32 timeStep = 1 / 60.0f;      //the length of time passed to simulate (seconds)
int32 velocityIterations = 8;   //how strongly to correct velocity
int32 positionIterations = 3;   //how strongly to correct position
DebugDraw g_draw;

void initManagers()
{
	TDF::SDL_Manager::StartModule();
	g_SDLManager = TDF::SDL_Manager::GetPointerInstance();
	g_SDLManager->init();
	g_SDLManager->setWindowTitle("TwoDee");

	TDF::ResourceManager::StartModule();
	g_ResourceManager = TDF::ResourceManager::GetPointerInstance();

	TDF::BoidManager::StartModule();
	g_BoidManager = TDF::BoidManager::GetPointerInstance();

	TDF::RenderManager::StartModule();
	g_RenderManager = TDF::RenderManager::GetPointerInstance();
	g_RenderManager->init();

#ifdef _WIN64

#else
	TDF::AnttweakbarManager::StartModule();
	g_AnttweakbarManager = TDF::AnttweakbarManager::GetPointerInstance();
	g_AnttweakbarManager->init();
	g_AnttweakbarManager->hideBars(true);
#endif

	myWorld->SetAllowSleeping(true);
	g_draw.SetFlags(b2Draw::e_shapeBit);
	myWorld->SetDebugDraw(&g_draw);
	g_draw.init(g_RenderManager->m_renderer);
}

void initContent()
{
	g_player.init(myWorld);
}

void render()
{
	g_RenderManager->setRenderTarget(g_RenderManager->m_renderTargets[TDF::GBUFFER]);
	g_RenderManager->setRenderDrawColor(0xFF, 0xFF, 0xFF);
	g_RenderManager->renderClear();

	g_player.render();

	g_BoidManager->render();

#ifdef _WIN64

#else
	g_AnttweakbarManager->render();
#endif

	myWorld->DrawDebugData();

	g_RenderManager->setRenderTarget();
	g_RenderManager->setRenderDrawColor(0xFF, 0xFF, 0xFF);
	g_RenderManager->renderClear();

	//g_RenderManager->saveTextureAsPNG("test", g_RenderManager->m_renderTargets[TDF::GBUFFER]);
	g_RenderManager->renderTexture(g_RenderManager->m_renderTargets[TDF::GBUFFER], 0, 0);

	g_RenderManager->renderPresent();
}

void update(float _deltaTime)
{
	g_SDLManager->update(_deltaTime);
	g_BoidManager->update(_deltaTime);

	g_player.update(_deltaTime);

	myWorld->Step(timeStep, velocityIterations, positionIterations);
}

void handleInputs()
{
	while (SDL_PollEvent(&g_SDLManager->m_events))
	{

#ifdef _WIN64
		g_guiHandled = 0;
#else
		g_AnttweakbarManager->handleEvent(&g_SDLManager->m_events);
		g_guiHandled = g_AnttweakbarManager->m_handled;
#endif
		
		if (!g_guiHandled)
		{
			if (g_SDLManager->m_events.type == SDL_WINDOWEVENT)
			{
				switch (g_SDLManager->m_events.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					g_SDLManager->updateWindowSize();
#ifdef _WIN64

#else
					g_AnttweakbarManager->updateWindowSize();
#endif
					break;
				}
			}

			if (g_SDLManager->m_events.type == SDL_QUIT)
			{
				g_quit = true;
			}

			if (g_SDLManager->m_events.type == SDL_KEYDOWN)
			{
				switch (g_SDLManager->m_events.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					g_quit = true;
					break;

				case SDLK_LALT:
					g_lAlt = true;
					break;

				case SDLK_d:
					g_player.moveState = MS_RIGHT;
					break;

				case SDLK_a:
					g_player.moveState = MS_LEFT;
					break;

				case SDLK_w:
					g_player.m_velocity = TDF::Vector2D(0, -g_player.m_movementSpeed);
					break;

				case SDLK_s:
					g_player.m_velocity = TDF::Vector2D(0, g_player.m_movementSpeed);
					break;

				case SDLK_RETURN:
					if (g_lAlt)
					{
						g_SDLManager->m_fullscreen ^= 1;
						g_SDLManager->setFullscreen(g_SDLManager->m_fullscreen);
					}
					break;
				}
			}

			if (g_SDLManager->m_events.type == SDL_KEYUP)
			{
				switch (g_SDLManager->m_events.key.keysym.sym)
				{
				case SDLK_LALT:
					g_lAlt = false;
					break;

				case SDLK_d:
					g_player.moveState = MS_STOP;
					break;

				case SDLK_a:
					g_player.moveState = MS_STOP;
					break;

				case SDLK_w:
					g_player.m_velocity.y = 0;
					break;

				case SDLK_s:
					g_player.m_velocity.y = 0;
					break;
				}
			}
		}
	}
}

int main()
{
	initManagers();

	initContent();

	while (!g_quit)
	{
		g_lastTime = g_time;
		g_time = SDL_GetPerformanceCounter();

		g_deltaTime = (float)((g_time - g_lastTime) * 1000.0f / SDL_GetPerformanceFrequency());
		g_deltaTime /= 1000.0f;

		g_deltaTime = 1 / 60.0f;

		render();
		handleInputs();
		update(g_deltaTime);
	}

#ifdef _WIN64

#else
	g_AnttweakbarManager->release();
#endif
	
	g_SDLManager->release();

	
	return 0;
}