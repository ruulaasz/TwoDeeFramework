#pragma once

#include<TDF.h>

enum CollisionID
{
	CI_PLATFORM = 1,
	CI_ENEMY
};

class Platform: public TDF::Actor
{
public:
	Platform();
	~Platform();

	virtual void update(float _deltaTime) { _deltaTime; };
	virtual void init() {};
	virtual void render() {};
	virtual void onEnterCollision(int _tag) { _tag; };
	virtual void dispatchMessage(const TDF::InputMessage& _message) { _message; };
};

