#pragma once

#include <TDF.h>

class Jaws : public TDF::Actor
{
public:
	Jaws();
	~Jaws();

	virtual void render();
	virtual void init();
	virtual void update(float _deltaTime);

	float m_damageMod;
	std::shared_ptr<TDF::Animation> m_jawsAnim;
	bool m_flipped;
};