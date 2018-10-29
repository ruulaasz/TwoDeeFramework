#pragma once

#include <TDF.h>

class Tail : public TDF::Actor
{
public:
	Tail();
	~Tail();

	virtual void render();
	virtual void init();
	virtual void update(float _deltaTime);

	float m_speedMod;

	TDF::Vector2D m_offset;

	std::shared_ptr<TDF::Texture> m_texture;
};

