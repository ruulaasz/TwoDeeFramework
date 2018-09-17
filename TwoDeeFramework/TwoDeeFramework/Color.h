#pragma once

namespace TDF
{
	class Color
	{
	public:
		Color();
		Color(int _r, int _g, int _b);
		~Color();

		int r;
		int g;
		int b;
	};
}