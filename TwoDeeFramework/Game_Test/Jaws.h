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

	TDF::Vector2D m_offset;

	std::shared_ptr<TDF::Texture> m_texture;
};

