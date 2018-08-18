#pragma once

#include <string>

namespace TDF
{
	//! An enum.
	/*! The types of resources available. */
	enum ResourceType
	{
		RT_DEFAULT = 0,
		RT_TEXTURE
	};

	//!  A base class for a resource.
	class Resource
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Resource();

		//! Default destructor.
		virtual ~Resource();

		//! A virtual function used to load the resource.
		/*!
		\param _path a string with the file path.
		*/
		virtual void load(std::string _path) {};

		//! A virtual function used to free the resource memory.
		virtual void free() {};

		//! Returns the resource name.
		std::string getName() { return m_name; };

		//! Returns the number of references of this resource.
		/*!
		\sa deleteReference(), addReference()
		*/
		unsigned int getReferenceCount() { return m_referenceCount; };

		//! Deletes 1 reference of the resource.
		/*!
		\sa getReferenceCount(), addReference()
		*/
		void deleteReference();

		//! Increase 1 reference of the resource.
		/*!
		\sa getReferenceCount(), deleteReference()
		*/
		void addReference();

	public:
		//! The type of the resource.
		ResourceType m_type;

	protected:
		//! The name of the resource.
		std::string m_name;

		//! The file path.
		std::string m_path;

		//! The number of times this resource its beign shared at 0 the resources gets freed.
		unsigned int m_referenceCount;
	};
}