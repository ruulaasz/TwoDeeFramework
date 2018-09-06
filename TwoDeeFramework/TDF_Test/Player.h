#pragma once

#include <TDF.h>

//enumeration of possible input states
enum MoveState
{
	MS_STOP = 0,
	MS_LEFT,
	MS_RIGHT
};

enum CollisionID
{
	CI_PLATFORM = 1,
	CI_ENEMY
};

class Player : public TDF::Actor
{
public:
	Player();
	~Player();

	virtual void update(float _deltaTime);
	virtual void init();
	virtual void render();
	virtual void onEnterCollision(int _tag);

public:
	TDF::Texture* m_texture;
	float m_movementSpeed;
	float m_jumpSpeed;
	TDF::Vector2D m_position;
	TDF::Vector2D m_velocity;
	float m_angle;

	b2Body* body;
	MoveState moveState;
	b2World* world;
	bool m_canJump;
	int m_jumpLimit;
	int m_currentJumps;

	TDF::ContactListener m_contactListener;

	void jump();

#ifdef _WIN64

#else
	TwBar* infoBar;
#endif
};