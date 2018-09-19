#include "Text.h"

namespace TDF
{
	Text::Text()
	{
		m_font = nullptr;
		m_text = "text";
	}

	Text::~Text()
	{
		TTF_CloseFont(m_font);
	}

	void Text::loadFromFile(std::string _path)
	{
		//Open the font 
		m_font = TTF_OpenFont(_path.c_str(), 28);

		if(m_font == nullptr )
		{ 
			printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );  
		} 
	}

	void Text::free()
	{

	}

	void Text::loadFromRenderedText(std::string textureText, SDL_Color textColor)
	{
		//Get rid of preexisting 
		m_texture.free();

		//Render text surface 
		SDL_Surface* textSurface = TTF_RenderText_Solid( m_font, textureText.c_str(), textColor ); 

		if( textSurface == NULL ) 
		{
			printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() ); 
		}
		else 
		{ 
			//Create texture from surface pixels 
			m_texture.m_sdlTexture = SDL_CreateTextureFromSurface( SDL_Manager::GetInstance().m_renderer, 
																   textSurface );

			if(m_texture.m_sdlTexture == NULL )
			{ 
				printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() ); 
			} 
			else 
			{ 
				//Get image dimensions 
				m_texture.m_width = textSurface->w; 
				m_texture.m_height = textSurface->h;
			} 

			//Get rid of old surface 
			SDL_FreeSurface( textSurface ); 
		} 
	}

	void Text::setStyle(int _style)
	{
		TTF_SetFontStyle(m_font, _style);
	}

	void Text::resizeText(int _size)
	{
		TTF_CloseFont(m_font);

		m_font = TTF_OpenFont(m_path.c_str(), _size);

		SDL_Color textColor = { m_textColor.r, m_textColor.g, m_textColor.b };

		loadFromRenderedText(m_text, textColor);
	}

	void Text::setColor(Color _color)
	{
		m_textColor = _color;

		SDL_Color textColor = { m_textColor.r, m_textColor.g, m_textColor.b };

		loadFromRenderedText(m_text, textColor);
	}

	void Text::setText(std::string _text)
	{
		m_text = _text;

		SDL_Color textColor = { m_textColor.r, m_textColor.g, m_textColor.b };

		loadFromRenderedText(m_text, textColor);
	}
}