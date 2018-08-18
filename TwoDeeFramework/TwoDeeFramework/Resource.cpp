#include "Resource.h"

namespace TDF
{
	Resource::Resource()
	{
		m_referenceCount = 0;
	}

	Resource::~Resource()
	{

	}

	void Resource::deleteReference()
	{
		m_referenceCount--;
		
		if (m_referenceCount <= 0)
		{
			m_referenceCount = 0;
		}
	}

	void Resource::addReference()
	{
		m_referenceCount++;
	}
}