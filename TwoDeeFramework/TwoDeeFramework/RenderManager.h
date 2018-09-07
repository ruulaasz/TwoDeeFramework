#pragma once

#include "SDL_Manager.h"
#include "Texture.h"
#include "Text.h"

namespace TDF
{
	class Circle;
	class AABB;
	class Vector2D;

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

		//! Render a circle
		/*!
		\param _circle the circle to render
		*/
		void renderCircle(const Circle& _circle);

		//! Render a box
		/*!
		\param _box the box to render.
		*/
		void renderBox(const AABB& _box);

		//! Render a box
		/*!
		\param _position, the position of the box.
		\param _w, the width of the box.
		\param _h, the height of the box.
		*/
		void renderBox(const Vector2D& _position, float _width, float _height);

		//! Render the texture in a given position.
		/*!
		\param _x an integer for the X position.
		\param _y an integer for the Y position.
		\param _angle the rotation angle of the texture.
		\param _flip if the texture is going to be flipped in the given direction.
		*/
		void renderTexture(Texture* _texture, 
						   int _x, 
						   int _y, 
						   float _angle = 0, 
						   SDL_RendererFlip _flip = SDL_FLIP_NONE);

		void renderText(Text* _text, std::string _data, int _x, int _y);

		//! Saves the given texture into a file.
		/*!
		\param _name the name of the file.
		\param _texture the texture to save.
		*/
		void saveTextureAsPNG(const char* _name, Texture* _texture);

		//! Set the render color.
		/*!
		\param _r, the red chanel.
		\param _g, the green chanel.
		\param _b, the blue chanel.
		\param _a, the alpha chanel.
		*/
		void setRenderDrawColor(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = SDL_ALPHA_OPAQUE);

		//! Set the current render target.
		/*!
		\param _newRenderTarget the new render target.
		*/
		void setRenderTarget(Texture* _newRenderTarget = nullptr);

		//! clears the current render target.
		void renderClear();

		//! Present the render into the screen.
		void renderPresent();

		//! a pointer to the device renderer.
		SDL_Renderer* m_renderer;

		//! the render targets for deferred rendering.
		Texture* m_renderTargets[MAX_TARGETS];
	};
}