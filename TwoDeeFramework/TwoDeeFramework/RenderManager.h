#pragma once

#include "SDL_Manager.h"
#include "Texture.h"

namespace TDF
{
	enum TargetContent
	{
		GBUFFER = 0,
		DEBUGHUD,
		TARGET2,
		TARGET3,
		TARGET4,
		TARGET5,
		TARGET6,
		TARGET7,
		MAX_TARGETS
	};

	class RenderManager : public Module<RenderManager>
	{
	public:
		RenderManager();
		~RenderManager();

		//! Initialize SDL 2.0 subsystems and creates the window and renderer.
		/*!
		\sa initSubSystems(), createWindowAndRenderer()
		*/
		void init();

		//! Render a circle
		/*!
		\param _r an integer, the radius of the circle.
		\param _cx an integer, the X position.
		\param _cy an integer, the Y position.
		*/
		void renderCircle(int _r, int _cx, int _cy);

		//! Render the texture in a given position.
		/*!
		\param _x an integer for the X position.
		\param _y an integer for the Y position.
		*/
		void renderTexture(TDF::Texture* _texture, int _x, int _y, float _angle = 0, SDL_RendererFlip _flip = SDL_FLIP_NONE);

		void saveTextureAsPNG(const char* _name, Texture* _texture);

		SDL_Renderer* m_renderer;
		Texture* m_renderTargets[MAX_TARGETS];
	};
}