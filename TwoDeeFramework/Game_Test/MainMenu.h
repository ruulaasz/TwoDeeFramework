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

private:
	void checkButtons();
	void lightEffect(float _deltaTime);

public:
	//background textures
	TDF::Texture* m_background[BACKGROUND_TEXTURES];

	//menu buttons
	TDF::TextButton m_newGameB;
	TDF::TextButton m_quitGameB;

	//music and sfx
	TDF::Music* m_titleMusic;

	//select animation
	TDF::Animation* m_selectAnim;
	TDF::Vector2D m_selectPosition;

	//grass animation
	TDF::Animation* m_grassAnim;
	
private:
	//light effect
	float m_lightAlpha;
	float m_alphaTarget;
};