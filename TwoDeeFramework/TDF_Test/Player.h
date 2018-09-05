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
	float m_movementSpeed;
	TDF::Vector2D m_position;
	TDF::Vector2D m_velocity;

#ifdef _WIN64

#else
	TwBar* infoBar;
#endif
};