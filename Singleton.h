#pragma once

#include <Windows.h>
#include <assert.h>

template < typename T > class Singleton
{
protected:
	static T* ms_Singleton;

public:
	Singleton()
	{
		assert(!ms_Singleton);
		int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
		ms_Singleton = (T*)((int)this + offset);
	}

	~Singleton()
	{
		assert(ms_Singleton);
		ms_Singleton = 0;
	}

	static T& GetSingleton()
	{
		assert(ms_Singleton);
		return (*ms_Singleton);
	}

	static T* GetSingletonPtr()
	{
		return (ms_Singleton);
	}
};