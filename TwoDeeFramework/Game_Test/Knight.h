#pragma once

#include <TDF.h>

class Knight : public TDF::Actor
{
public:
	Knight();
	~Knight();

	virtual void update(float _deltaTime);
	virtual void init();
	virtual void render();
	virtual void onEnterCollision(int _tag);
	virtual void dispatchMessage(const TDF::InputMessage& _message);

	void setDirection(int _dir);
	void jump();
	void setWorld(TDF::World* _world) { m_psysicsWorld = _world->m_physicsWorld; };

public:
	std::shared_ptr<TDF::Texture> m_texture;
	float m_movementSpeed;
	float m_jumpSpeed;
	TDF::Vector2D m_position;
	TDF::Vector2D m_velocity;

	bool m_canJump;
	int m_jumpLimit;
	int m_currentJumps;

	TDF::ContactListener m_contactListener;

	std::shared_ptr<TDF::Sfx> m_jumpSFX;
	b2Body* m_dynamicBody;
	b2World* m_psysicsWorld;

	TwBar* infoBar;

};