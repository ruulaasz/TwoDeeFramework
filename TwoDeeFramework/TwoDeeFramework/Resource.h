#pragma once

#include "StdHeaders.h"

namespace TDF
{
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
		virtual void loadFromFile(string _path) = 0;

		//! A virtual function used to free the resource memory.
		virtual void free() = 0;

		//! Returns the resource name.
		void setName(const string& _name) { m_name = _name; };

		//! Returns the resource file path.
		void setPath(const string& _path) { m_path = _path; };

	public:
		//! The name of the resource.
		string m_name;

		//! The file path.
		string m_path;
	};
}