#include "Color.h"

namespace TDF
{
	Color::Color()
	{
		a = SDL_ALPHA_OPAQUE;
	}

	Color::Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a)
	{
		r = _r;
		g = _g; 
		b = _b;
		a = _a;
	}

	Color::~Color()
	{

	}
}