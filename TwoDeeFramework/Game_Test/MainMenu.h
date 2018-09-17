#pragma once

#include <TDF.h>

#define BACKGROUND_TEXTURES 8

class MainMenu : public TDF::Scene
{
public:
	MainMenu();
	~MainMenu();

	virtual void onEnter();
	virtual void onExit();
	virtual void update(float _deltaTime);
	virtual void render();

	void reset();

public:
	TDF::Texture* m_background[BACKGROUND_TEXTURES];

	TDF::TextButton m_newGameB;
	TDF::TextButton m_quitGameB;

private:
	float m_lightAlpha;
	float m_alphaTarget;
};