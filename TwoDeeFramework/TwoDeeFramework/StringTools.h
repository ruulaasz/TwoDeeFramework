#pragma once

#include "StdHeaders.h"

namespace TDF
{
	//!  Get the name of a file using the its path.
	/*!
	return A string with the resource name.
	*/
	static string getNameFromPath(string _path)
	{
		string name;

		size_t i = _path.length();
		i--;

		for (i; i >= 0; i--)
		{
			if (_path.at(i) == 92)
			{
				break;
			}

			name.push_back(_path.at(i));
		}

		reverse(name.begin(), name.end());

		i = 0;

		for (i; i < 4; i++)
		{
			name.pop_back();
		}

		return name;
	}
}