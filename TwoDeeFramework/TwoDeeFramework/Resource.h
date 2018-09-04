#pragma once

#include <string>

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
		virtual void loadFromFile(std::string _path) = 0;

		//! A virtual function used to free the resource memory.
		virtual void free() = 0;

		//! Returns the resource name.
		std::string getName() { return m_name; };

		//! Returns the resource name.
		void setName(std::string _name) { m_name = _name; };

	protected:
		//! The name of the resource.
		std::string m_name;

		//! The file path.
		std::string m_path;
	};
}