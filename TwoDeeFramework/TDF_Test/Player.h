#pragma once

#include <TDF.h>

class Player : public TDF::Actor
{
public:
	Player();
	~Player();

	TDF::Texture* m_texture;

	int m_posX;
	int m_posY;
	bool m_enable;

	void init();
	void render();
	void destroy();
};