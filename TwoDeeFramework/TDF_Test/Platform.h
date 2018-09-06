#pragma once

#include<TDF.h>

class Platform: public TDF::Actor
{
public:
	Platform();
	~Platform();

	virtual void update(float _deltaTime) {};
	virtual void init() {};
	virtual void render() {};
	virtual void onEnterCollision(int _tag) {};
};

