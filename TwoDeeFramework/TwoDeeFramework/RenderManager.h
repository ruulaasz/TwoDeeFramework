#pragma once

#include "SDL_Manager.h"
#include "Texture.h"

namespace TDF
{
	//!  A enum for a render target usages.
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

	//!  A manager class for rendering.
	class RenderManager : public Module<RenderManager>
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		RenderManager();

		//! Default destructor.
		~RenderManager();

		//! Initialize the render targets.
		void init();

		//! Render a circle
		/*!
		\param _r an integer, the radius of the circle.
		\param _cx a float, the X position.
		\param _cy a float, the Y position.
		*/
		void renderCircle(float _r, float _cx, float _cy);

		//! Render the texture in a given position.
		/*!
		\param _x an integer for the X position.
		\param _y an integer for the Y position.
		*/
		void renderTexture(TDF::Texture* _texture, 
						   int _x, 
						   int _y, 
						   float _angle = 0, 
						   SDL_RendererFlip _flip = SDL_FLIP_NONE);


		//! Saves the given texture into a file.
		/*!
		\param _name the name of the file.
		\param _texture the texture to save.
		*/
		void saveTextureAsPNG(const char* _name, Texture* _texture);

		//! a pointer to the device renderer.
		SDL_Renderer* m_renderer;

		//! the render targets for deferred rendering.
		Texture* m_renderTargets[MAX_TARGETS];
	};
}