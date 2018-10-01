#include "Font.h"

namespace TDF
{
	Font::Font()
	{
		m_font = nullptr;
	}

	Font::~Font()
	{
		TTF_CloseFont(m_font);
	}

	void Font::loadFromFile(string _path)
	{
		//Open the font 
		m_font = TTF_OpenFont(_path.c_str(), 28);

		if (m_font == nullptr)
		{
			printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		}
	}

	void Font::free()
	{

	}
}