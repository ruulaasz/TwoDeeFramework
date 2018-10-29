#pragma once

#include <TDF.h>

#include "Tail.h"
#include "Jaws.h"
#include "Fin.h"

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

public:
	std::shared_ptr<TDF::Texture> m_texture;

	float m_movementSpeed;

	TDF::Vector2D m_velocity;

	TDF::ContactListener m_contactListener;
	TDF::DynamicBody m_dynamicBody;

	TwBar* infoBar;

	Tail* m_tail;
	Jaws* m_jaws;
	Fin* m_fin;

	std::shared_ptr<TDF::Animation> m_grassAnim;
	bool m_flipped;
};