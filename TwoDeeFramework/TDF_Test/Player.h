#pragma once

#include <TDF.h>

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
	virtual void dispatchMessage(const TDF::InputMessage& _message);

	void setDirection(int _dir);

public:
	TDF::Texture* m_texture;
	TDF::Text* m_nameText;
	float m_movementSpeed;
	float m_jumpSpeed;
	TDF::Vector2D m_position;
	TDF::Vector2D m_velocity;
	float m_angle;

	b2Body* body;
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