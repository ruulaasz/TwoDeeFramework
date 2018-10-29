#pragma once

#include <TDF.h>
#include "EvoCube.h"

class LevelEvo : public TDF::Scene
{
public:
	LevelEvo();
	~LevelEvo();

	virtual void onEnter();
	virtual void onExit();

	virtual void update(float _deltaTime);
	virtual void render();
	virtual void init();

	EvoCube* m_player;
};