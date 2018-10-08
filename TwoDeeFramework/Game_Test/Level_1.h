#pragma once

#include <TDF.h>

class Knight;

class Level_1 : public TDF::Scene
{
public:
	Level_1();
	~Level_1();

	virtual void onEnter();
	virtual void onExit();

	virtual void update(float _deltaTime);
	virtual void render();
	virtual void init();

	Knight* m_player;
};

