#pragma once

#include "StringTools.h"
#include "Module.h"
#include "SDL_Manager.h"
#include "RenderManager.h"
#include "Box2DManager.h"

#ifdef _WIN64

#else
#include "AnttweakbarManager.h"
#endif

#include "Resource.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Vector2D.h"
#include "AABB.h"
#include "Circle.h"
#include "Actor.h"
#include "PathNode.h"
#include "Boid.h"
#include "BoidManager.h"
#include "World.h"
#include "ContactListener.h"
#include "InputMessage.h"
#include "InputManager.h"
#include "SystemManager.h"
#include "Sfx.h"
#include "Music.h"
#include "AudioManager.h"
#include "Timer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Color.h"
#include "Button.h"
#include "TextButton.h"