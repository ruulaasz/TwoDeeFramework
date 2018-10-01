#include "Text.h"

namespace TDF
{
	Text::Text()
	{
		m_font = nullptr;
		m_text = "text";
		m_texture = Shared_Ptr<Texture>(new Texture);
	}

	Text::~Text()
	{
		
	}

	void Text::loadFromFile(string _path)
	{

	}

	void Text::loadFromRenderedText(string textureText, SDL_Color textColor)
	{
		//Get rid of preexisting 
		m_texture.get()->free();

		//Render text surface 
		SDL_Surface* textSurface = TTF_RenderText_Solid( m_font.get()->m_font, textureText.c_str(), textColor );

		if( textSurface == NULL ) 
		{
			printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() ); 
		}
		else 
		{ 
			//Create texture from surface pixels 
			m_texture.get()->m_sdlTexture = SDL_CreateTextureFromSurface( SDL_Manager::GetInstance().m_renderer, 
																   textSurface );

			if(m_texture.get()->m_sdlTexture == NULL )
			{ 
				printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() ); 
			} 
			else 
			{ 
				//Get image dimensions 
				m_texture.get()->m_width = textSurface->w;
				m_texture.get()->m_height = textSurface->h;
			} 

			//Get rid of old surface 
			SDL_FreeSurface( textSurface ); 
		} 
	}

	void Text::setStyle(int _style)
	{
		TTF_SetFontStyle(m_font.get()->m_font, _style);
	}

	void Text::resizeText(int _size)
	{
		TTF_CloseFont(m_font.get()->m_font);

		m_font.get()->m_font = TTF_OpenFont(m_font.get()->m_path.c_str(), _size);

		SDL_Color textColor = { m_textColor.r, m_textColor.g, m_textColor.b };

		loadFromRenderedText(m_text, textColor);
	}

	void Text::setColor(Color _color)
	{
		m_textColor = _color;

		SDL_Color textColor = { m_textColor.r, m_textColor.g, m_textColor.b };

		loadFromRenderedText(m_text, textColor);
	}

	void Text::setText(string _text)
	{
		m_text = _text;

		SDL_Color textColor = { m_textColor.r, m_textColor.g, m_textColor.b };

		loadFromRenderedText(m_text, textColor);
	}
}