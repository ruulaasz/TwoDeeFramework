#pragma once

#include <TDF.h>

class Level_0 : public TDF::Scene
{
public:
	Level_0();
	~Level_0();

	virtual void onEnter();
	virtual void onExit();

	virtual void update(float _deltaTime);
	virtual void render();
	virtual void init();
};

