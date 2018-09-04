#pragma once

#include <TDF.h>

class Player : public TDF::Actor
{
public:
	Player();
	~Player();

	void update(float _deltaTime);
	void init();
	void render(float _angle = 0);
	void destroy();

public:
	TDF::Texture* m_texture;
	bool m_enable;
	TDF::Vector2D m_position;

#ifdef _WIN64

#else
	TwBar* m_steerBar;
	double vel[3];
	double des[3];
	double steer[3];
#endif
};