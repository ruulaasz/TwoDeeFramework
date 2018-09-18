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
	//background textures
	TDF::Texture* m_background[BACKGROUND_TEXTURES];

	//menu buttons
	TDF::TextButton m_newGameB;
	TDF::TextButton m_quitGameB;

	//music and sfx
	TDF::Music* m_titleTheme;

	//test animation
	TDF::Animation* m_grassAnimation;
	
private:
	//light effect
	float m_lightAlpha;
	float m_alphaTarget;
};