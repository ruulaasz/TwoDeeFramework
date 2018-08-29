#include <cstdio>
#include <windows.h>

#include <TDF.h>
#include "Player.h"

TDF::SDL_Manager* g_SDLManager;
TDF::ResourceManager* g_ResourceManager;
TDF::BoidManager* g_BoidManager;

#ifdef _WIN64

#else
TDF::AnttweakbarManager* g_AnttweakbarManager;
#endif

Uint64 g_time = SDL_GetPerformanceCounter();
Uint64 g_lastTime = 0;
float g_deltaTime = 0;

bool g_quit;
bool g_lAlt;
int g_guiHandled;

Player g_player;

TDF::Boid* Seeker;
TDF::Boid* Seeker2;
TDF::Boid* Seeker3;

TDF::Boid* Prey;
TDF::Boid* Mouse;

void initSDL()
{
	TDF::SDL_Manager::StartModule();
	g_SDLManager = TDF::SDL_Manager::GetPointerInstance();
	g_SDLManager->init();
	SDL_SetWindowTitle(g_SDLManager->m_window, "Test");

	TDF::ResourceManager::StartModule();
	g_ResourceManager = TDF::ResourceManager::GetPointerInstance();

	TDF::BoidManager::StartModule();
	g_BoidManager = TDF::BoidManager::GetPointerInstance();
}

#ifdef _WIN64

#else
void initTw()
{
	TDF::AnttweakbarManager::StartModule();
	g_AnttweakbarManager = TDF::AnttweakbarManager::GetPointerInstance();
	g_AnttweakbarManager->init();
}
#endif

void loadContent()
{
	Seeker = new TDF::Boid();
	Seeker2 = new TDF::Boid();
	Seeker3 = new TDF::Boid();

	Prey = new TDF::Boid();
	Mouse = new TDF::Boid();

	g_player.init();

	Seeker->m_target = Prey;
	Seeker->m_position = TDF::Vector2D(0, 0);
	Seeker->m_behaviors = TDF::BT_FOLLOWLEADER;

	Seeker2->m_target = Prey;
	Seeker2->m_position = TDF::Vector2D(0, 1000);
	Seeker2->m_behaviors = TDF::BT_FOLLOWLEADER;

	Seeker3->m_target = Prey;
	Seeker3->m_position = TDF::Vector2D(200, 500);
	Seeker3->m_behaviors = TDF::BT_FOLLOWLEADER;

	//Seeker->m_path.push_back(new TDF::PathNode(TDF::Vector2D(1000, 500), 50));
	//Seeker->m_path.push_back(new TDF::PathNode(TDF::Vector2D(1000, 900), 50));
	//Seeker->m_path.push_back(new TDF::PathNode(TDF::Vector2D(1500, 500), 50));
	g_BoidManager->m_allBoids.push_back(Seeker);
	g_BoidManager->m_allBoids.push_back(Seeker2);
	g_BoidManager->m_allBoids.push_back(Seeker3);

	Prey->m_position = TDF::Vector2D(1000, 300);
	Prey->m_target = Mouse;
	Prey->m_seekScalar = 5;
	//Prey->m_maxVelocity = 6;
	Prey->m_behaviors = TDF::BT_SEEK;
	g_BoidManager->m_allBoids.push_back(Prey);

	//g_BoidManager->m_obstacles.push_back(new TDF::CircleObstacle(TDF::Vector2D(1000, 500), 100));
	//g_BoidManager->m_obstacles.push_back(new TDF::CircleObstacle(TDF::Vector2D(500, 500), 200));
	//g_BoidManager->m_obstacles.push_back(new TDF::CircleObstacle(TDF::Vector2D(1000, 800), 75));
}

void renderBoids()
{
	g_player.m_posX = Prey->m_position.x;
	g_player.m_posY = Prey->m_position.y;
	g_player.render();

	g_player.m_posX = Seeker->m_position.x;
	g_player.m_posY = Seeker->m_position.y;

	if (TDF::getLength(Seeker->m_velocity) > 0)
	{
		Seeker->m_renderDirection = Seeker->m_velocity;
	}
	g_player.render((float)std::atan2(Seeker->m_renderDirection.x, -Seeker->m_renderDirection.y));

	g_player.m_posX = Seeker2->m_position.x;
	g_player.m_posY = Seeker2->m_position.y;

	if (TDF::getLength(Seeker2->m_velocity) > 0)
	{
		Seeker2->m_renderDirection = Seeker2->m_velocity;
	}
	g_player.render((float)std::atan2(Seeker2->m_renderDirection.x, -Seeker2->m_renderDirection.y));

	g_player.m_posX = Seeker3->m_position.x;
	g_player.m_posY = Seeker3->m_position.y;

	if (TDF::getLength(Seeker3->m_velocity) > 0)
	{
		Seeker3->m_renderDirection = Seeker3->m_velocity;
	}
	g_player.render((float)std::atan2(Seeker3->m_renderDirection.x, -Seeker3->m_renderDirection.y));
}

void render()
{
	SDL_SetRenderDrawColor(g_SDLManager->m_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(g_SDLManager->m_renderer);

	renderBoids();

	g_BoidManager->render();

	for (size_t i = 0; i < g_BoidManager->m_obstacles.size(); i++)
	{
		g_BoidManager->m_obstacles.at(i)->render();
	}

#ifdef _WIN64

#else
	g_AnttweakbarManager->render();
#endif

	SDL_RenderPresent(g_SDLManager->m_renderer);
}

void update(float _deltaTime)
{
	g_SDLManager->update(_deltaTime);
	g_ResourceManager->update(_deltaTime);
	g_BoidManager->update(_deltaTime);
	Mouse->m_position.x = g_SDLManager->m_mousePosX;
	Mouse->m_position.y = g_SDLManager->m_mousePosY;
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
					SDL_GetWindowSize(g_SDLManager->m_window, &g_SDLManager->m_windowWidth, &g_SDLManager->m_windowHeight);
#ifdef _WIN64

#else
					TwWindowSize(g_SDLManager->m_windowWidth, g_SDLManager->m_windowHeight);
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
				}
			}
		}
	}
}

int main()
{
	initSDL();

#ifdef _WIN64

#else
	initTw();
#endif

	loadContent();

	while (!g_quit)
	{
		g_lastTime = g_time;
		g_time = SDL_GetPerformanceCounter();

		g_deltaTime = (float)((g_time - g_lastTime) * 1000 / SDL_GetPerformanceFrequency());
		g_deltaTime /= 1000.f;

		handleInputs();
		update(g_deltaTime);
		render();
	}

#ifdef _WIN64

#else
	g_AnttweakbarManager->release();
#endif
	
	g_SDLManager->release();
	return 0;
}