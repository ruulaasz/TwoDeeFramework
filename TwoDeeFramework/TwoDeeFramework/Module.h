#pragma once

namespace TDF
{
	//!  A template module class. 
	/*!
	Used to get acces to a manager class everywere.
	*/
	template<class _type>
	class Module
	{
	protected:
		static _type*& instance() 
		{
			static _type* instance = NULL;
			return instance;
		}

	public:
		static void StartModule()
		{
			instance() = new _type();
		}
		static _type& GetInstance()
		{
			return *instance();
		}
		static _type* GetPointerInstance()
		{
			return instance();
		}
		static void CloseModule()
		{
			instance()->Release();
			delete instance();
			instance() = NULL;
		}
	public:
		Module() {}
		virtual ~Module() {}
	};
}