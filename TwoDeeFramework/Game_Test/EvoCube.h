#pragma once

#include <TDF.h>

#include "Jaws.h"

enum DIRECTIONS
{
	D_STOP=0,
	D_STOPX,
	D_STOPY,
	D_RIGHT,
	D_LEFT,
	D_UP,
	D_DOWN
};

class EvoCube : public TDF::Actor
{
public:
	EvoCube();
	~EvoCube();

	virtual void update(float _deltaTime);
	virtual void init();
	virtual void render();
	virtual void onEnterCollision(int _tag);
	virtual void dispatchMessage(const TDF::InputMessage& _message);

	void setDirection(int _dir);
	void enterScene(std::string _sceneName);
	void updateCamera();
	void updateBodyParts(float _deltaTime);

public:
	float m_movementSpeed;

	TDF::Vector2D m_velocity;

	TDF::ContactListener m_contactListener;
	TDF::DynamicBody m_dynamicBody;

	TwBar* infoBar;

	Jaws* m_jaws;

	std::shared_ptr<TDF::Animation> m_bodyAnim;
	bool m_flipped;

private:
	TDF::Vector2D m_renderPos;
};