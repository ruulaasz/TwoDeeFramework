#include "RenderManager.h"

namespace TDF
{
	RenderManager::RenderManager()
	{
		m_renderer = nullptr;
	}

	RenderManager::~RenderManager()
	{

	}

	void RenderManager::init()
	{
		m_renderer = SDL_Manager::GetInstance().m_renderer;

		for (size_t i = 0; i < MAX_TARGETS; i++)
		{
			m_renderTargets[i] = new Texture();
			m_renderTargets[i]->createAsRenderTarget();
		}
	}

	void RenderManager::renderCircle(float _r, float _cx, float _cy)
	{
		double error = (double)-_r;
		double x = (double)_r - 0.5;
		double y = (double)0.5;
		double cx = _cx - 0.5;
		double cy = _cy - 0.5;

		while (x >= y)
		{
			SDL_RenderDrawPoint(m_renderer, (int)(cx + x), (int)(cy + y));
			SDL_RenderDrawPoint(m_renderer, (int)(cx + y), (int)(cy + x));

			if (x != 0)
			{
				SDL_RenderDrawPoint(m_renderer, (int)(cx - x), (int)(cy + y));
				SDL_RenderDrawPoint(m_renderer, (int)(cx + y), (int)(cy - x));
			}

			if (y != 0)
			{
				SDL_RenderDrawPoint(m_renderer, (int)(cx + x), (int)(cy - y));
				SDL_RenderDrawPoint(m_renderer, (int)(cx - y), (int)(cy + x));
			}

			if (x != 0 && y != 0)
			{
				SDL_RenderDrawPoint(m_renderer, (int)(cx - x), (int)(cy - y));
				SDL_RenderDrawPoint(m_renderer, (int)(cx - y), (int)(cy - x));
			}

			error += y;
			++y;
			error += y;

			if (error >= 0)
			{
				--x;
				error -= x;
				error -= x;
			}
		}
	}

	void RenderManager::renderTexture(TDF::Texture * _texture, int _x, int _y, float _angle, SDL_RendererFlip _flip)
	{
		SDL_Rect quadSrc = { 0, 0, _texture->m_width, _texture->m_height };
		SDL_Rect quadDst = { _x , _y , _texture->m_width, _texture->m_height };

		SDL_RenderCopyEx(m_renderer, 
						 _texture->m_sdlTexture, 
						 &quadSrc, 
						 &quadDst, 
						 (_angle), 
						 nullptr, 
						 _flip);
	}

	void RenderManager::saveTextureAsPNG(const char * _name, Texture * _texture)
	{
		SDL_Texture* target = SDL_GetRenderTarget(m_renderer);
		SDL_SetRenderTarget(m_renderer, _texture->m_sdlTexture);
		int width, height;
		SDL_QueryTexture(_texture->m_sdlTexture, NULL, NULL, &width, &height);
		SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

		SDL_RenderReadPixels(m_renderer, 
							 NULL, 
							 surface->format->format, 
							 surface->pixels, 
							 surface->pitch);

		IMG_SavePNG(surface, _name);
		SDL_FreeSurface(surface);
		SDL_SetRenderTarget(m_renderer, target);
	}
}