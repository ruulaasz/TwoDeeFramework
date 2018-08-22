#pragma once

#include <TDF.h>
#include <SB.h>

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
	SB::Vector2D m_position;
	SB::Vector2D m_velocity;
	float m_maxVelocity;

private:
	SB::SteeringBody m_body;
	TwBar* m_steerBar;
	SB::Target* m_target;
	double vel[3];
	double des[3];
	double steer[3];
};