#pragma once

#include <TDF.h>

class Player : public TDF::Actor
{
public:
	Player();
	~Player();

	void update(float _deltaTime);
	void init();
	void render();
	void destroy();

public:
	TDF::Texture* m_texture;
	bool m_enable;
	int m_posX;
	int m_posY;

#ifdef _WIN64

#else
	TwBar* m_steerBar;
	double vel[3];
	double des[3];
	double steer[3];
#endif
};