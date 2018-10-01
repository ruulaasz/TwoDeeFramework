#pragma once

#include <TDF.h>

class MainMenu : public TDF::Scene
{
public:
	MainMenu();
	~MainMenu();

	virtual void onEnter();
	virtual void onExit();

	virtual void update(float _deltaTime);
	virtual void render();
	virtual void init();

private:
	void checkButtons();
	void lightEffect(float _deltaTime);

public:
	//menu buttons
	TDF::TextButton m_newGameB;
	TDF::TextButton m_quitGameB;

	//select animation
	std::shared_ptr<TDF::Animation> m_selectAnim;
	TDF::Vector2D m_selectPosition;

	//grass animation
	std::shared_ptr<TDF::Animation> m_grassAnim;
	
private:
	//light effect
	float m_lightAlpha;
	float m_alphaTarget;
};