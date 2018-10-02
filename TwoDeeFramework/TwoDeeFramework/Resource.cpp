#include "Resource.h"
#include "StringTools.h"

namespace TDF
{
	Resource::Resource()
	{
		
	}

	Resource::~Resource()
	{

	}

	void Resource::loadFromFile(string _path)
	{
		setName(getNameFromPath(_path));
		setPath(_path);
	}

	void Resource::free()
	{

	}
}