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
	TDF::Vector2D m_position;
	TDF::Vector2D m_velocity;
	TDF::AABB m_mainCB;
};