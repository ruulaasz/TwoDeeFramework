#pragma once

#include <TDF.h>
#include "Knight.h"

class Level_1 : public TDF::Scene
{
public:
	Level_1();
	~Level_1();

	virtual void onEnter();
	virtual void onExit();

	virtual void update(float _deltaTime);
	virtual void render();
	virtual void init(TDF::PhysicsWorld* _physicWorld = nullptr);

	Knight m_player;
	TDF::Platform m_platform;
};

