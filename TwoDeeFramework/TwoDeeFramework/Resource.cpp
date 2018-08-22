#include "Resource.h"

namespace TDF
{
	Resource::Resource()
	{
		m_referenceCount = 0;
		m_type = RT_DEFAULT;
	}

	Resource::~Resource()
	{

	}

	void Resource::deleteReference()
	{
		if (m_referenceCount > 0)
		{
			m_referenceCount--;
		}
	}

	void Resource::addReference()
	{
		m_referenceCount++;
	}
}