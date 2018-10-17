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
	void enterScene(std::string _sceneName);

public:
	std::shared_ptr<TDF::Texture> m_texture;
	std::shared_ptr<TDF::Sfx> m_jumpSFX;

	float m_movementSpeed;
	float m_jumpSpeed;

	TDF::Vector2D m_velocity;

	bool m_canJump;
	int m_jumpLimit;
	int m_currentJumps;

	TDF::ContactListener m_contactListener;
	TDF::DynamicBody m_dynamicBody;

	TwBar* infoBar;
};