#pragma once

#include <TDF.h>
#include <Box2D.h>

//enumeration of possible input states
enum MoveState
{
	MS_STOP = 0,
	MS_LEFT,
	MS_RIGHT
};

class Player : public TDF::Actor
{
public:
	Player();
	~Player();

	void update(float _deltaTime);
	void init(b2World* _b2World);
	void render(float _angle = 0.0f);

public:
	TDF::Texture* m_texture;
	float m_movementSpeed;
	TDF::Vector2D m_position;
	TDF::Vector2D m_velocity;

	b2Body* body;
	MoveState moveState;

#ifdef _WIN64

#else
	TwBar* infoBar;
#endif
};