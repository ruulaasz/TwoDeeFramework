#include "Texture.h"
#include "StringTools.h"

namespace TDF
{
	Texture::Texture()
	{
		
	}

	Texture::~Texture()
	{
		
	}

	void Texture::load(std::string _path)
	{
		free();

		SDL_Texture* newTexture = nullptr;

		SDL_Surface* loadedSurface = IMG_Load(_path.c_str());

		if (loadedSurface == nullptr)
		{
			printf("Cannot load image %s SDL_image Error: %s\n", _path.c_str(), IMG_GetError());
		}
		else
		{
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

			newTexture = SDL_CreateTextureFromSurface(TDF::SDL_Manager::GetInstance().m_renderer, loadedSurface);

			if (newTexture == nullptr)
			{
				printf("Failed to create texture %s SDL Error: %s\n", _path.c_str(), SDL_GetError());
			}
			else
			{
				m_width = loadedSurface->w;
				m_height = loadedSurface->h;
			}

			SDL_FreeSurface(loadedSurface);
		}

		m_sdlTexture = newTexture;
		m_path = _path;
		m_name = getNameFromPath(m_path);
	}

	void Texture::free()
	{
		if (m_sdlTexture != nullptr)
		{
			m_width = 0;
			m_height = 0;
			deleteReference();
			SDL_DestroyTexture(m_sdlTexture);
			m_sdlTexture = nullptr;
		}
	}

	void Texture::render(int _x, int _y)
	{
		SDL_Rect quadSrc = { 0, 0, m_width, m_height };
		SDL_Rect quadDst = { _x, _y, m_width, m_height };
		SDL_RenderCopy(SDL_Manager::GetInstance().m_renderer, m_sdlTexture, &quadSrc, &quadDst);
	}
}